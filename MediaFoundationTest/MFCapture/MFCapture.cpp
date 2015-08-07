// これは メイン DLL ファイルです。

#include "stdafx.h"
#include "MFCapture.h"

namespace MFCapture
{
	VideoCapture::VideoCapture()
	{
		MFStartup(MF_VERSION);

		this->Config = NULL;
		this->Devices = NULL;
		this->Source = NULL;
		this->DeviceCount = 0;
		this->SourceReader = NULL;
		this->CallBack = NULL;
		this->InputMediaType = NULL;
	}

	VideoCapture::~VideoCapture()
	{
		MFShutdown();
	}

	bool VideoCapture::CreateMediaSource()
	{
		HRESULT hr;

		pin_ptr<IMFAttributes *> pConfig = &(this->Config);
		hr = MFCreateAttributes(pConfig, 1);
		if (hr != S_OK)
		{ 
			MFUtil::ShowErrorNameFromCode(hr);
			return false;
		}

		hr = this->Config->SetGUID(
			MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE, 
			MF_DEVSOURCE_ATTRIBUTE_SOURCE_TYPE_VIDCAP_GUID
		); 
		if (hr != S_OK)
		{ 
			MFUtil::ShowErrorNameFromCode(hr);
			return false;
		}

		pin_ptr<IMFActivate **> pDevices = &(this->Devices);
		pin_ptr<UINT32> pCount = &(this->DeviceCount);
		hr = MFEnumDeviceSources(this->Config, pDevices, pCount);
		if (hr != S_OK)
		{ 
			MFUtil::ShowErrorNameFromCode(hr);
			return false;
		}
		if (this->DeviceCount <= 0) 
		{ 
			MFUtil::ShowMessage(TEXT("Device Not Found."), ML_ERROR);
			return false;
		} 

		// Debug : 利用するデバイス（リストの先頭）の名前を確認
		LPWSTR devName = NULL;
		UINT32 devNameLen = 0;
		hr = this->Devices[0]->GetAllocatedString(MF_DEVSOURCE_ATTRIBUTE_FRIENDLY_NAME, &devName, &devNameLen);
		if (hr != S_OK)
		{ 
			MFUtil::ShowErrorNameFromCode(hr);
			return false;
		}
		MFUtil::ShowMessage(devName, ML_DEBUG);

		pin_ptr<IMFMediaSource *> pSource = &(this->Source);
		hr = this->Devices[0]->ActivateObject(
			__uuidof(IMFMediaSource), 
			reinterpret_cast<void**>(pSource)
		);  
		if (hr != S_OK)
		{ 
			MFUtil::ShowErrorNameFromCode(hr);
			return false;
		}

		return true;
	}

	HRESULT VideoCapture::CreateInputMediaType(GUID majorType, GUID subtype)
	{
		HRESULT hr;

		pin_ptr<IMFMediaType *> pInputMediaType = &(this->InputMediaType);		
		hr = MFCreateMediaType(pInputMediaType);
		if (hr != S_OK)
		{
			return hr;
		}

		hr = this->InputMediaType->SetGUID(MF_MT_MAJOR_TYPE, majorType);
		if (hr != S_OK)
		{
			return hr;
		}

		hr = this->InputMediaType->SetGUID(MF_MT_SUBTYPE, subtype);
		if (hr != S_OK)
		{
			return hr;
		}

        hr = this->InputMediaType->SetUINT32(
			MF_MT_INTERLACE_MODE, 
			MFVideoInterlace_Progressive
		);   
		if (hr != S_OK)
		{
			return hr;
		}

		hr = MFSetAttributeSize(
			this->InputMediaType, 
			MF_MT_FRAME_SIZE, 
			640, 480
		);   
		if (hr != S_OK)
		{
			return hr;
		}

		hr = MFSetAttributeRatio(
			this->InputMediaType, 
			MF_MT_FRAME_RATE, 
			30, 1
		);   
		if (hr != S_OK)
		{
			return hr;
		}

        hr = MFSetAttributeRatio(
			this->InputMediaType, 
			MF_MT_PIXEL_ASPECT_RATIO, 
			1, 1
		);   
		if (hr != S_OK)
		{
			return hr;
		}

		return hr;
	}

	HRESULT VideoCapture::ConfigureSourceReader()
	{
		HRESULT hr;
		IMFMediaType *pNativeType = NULL;
		GUID majorType;
		GUID subtype;

		hr = this->SourceReader->GetNativeMediaType(
			MF_SOURCE_READER_FIRST_VIDEO_STREAM, 
			0, 
			&pNativeType
		);
		if (hr != S_OK)
		{
			return hr;
		}

		hr = pNativeType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
		if (hr != S_OK)
		{
			return hr;
		}

		hr = pNativeType->GetGUID(MF_MT_SUBTYPE, &subtype);
		if (hr != S_OK)
		{
			return hr;
		}

		hr = this->CreateInputMediaType(majorType, subtype);
		if (hr != S_OK)
        {
			return hr;
        }

		hr = this->SourceReader->SetCurrentMediaType(
			MF_SOURCE_READER_FIRST_VIDEO_STREAM, 
			NULL, 
			this->InputMediaType
		);
		if (hr != S_OK)
        {
			return hr;
        }

	    GUID subtypes[] = { 
			MFVideoFormat_NV12, 
			MFVideoFormat_UYVY,
			MFVideoFormat_RGB32, 
			MFVideoFormat_RGB24, 
			MFVideoFormat_IYUV,
			MFVideoFormat_YUY2
		};
		bool isSubtypeSetted = false;

		for (UINT32 i = 0; i < ARRAYSIZE(subtypes); i++)
        {
			if (subtype == subtypes[i])
			{
				isSubtypeSetted = true;
				break;
			}
        }
		if (isSubtypeSetted)
		{
			return hr;
		}

		for (UINT32 i = 0; i < ARRAYSIZE(subtypes); i++)
		{
			hr = this->InputMediaType->SetGUID(MF_MT_SUBTYPE, subtypes[i]);
			if (hr != S_OK)
			{
				return hr;
			}

			hr = this->SourceReader->SetCurrentMediaType(
				MF_SOURCE_READER_FIRST_VIDEO_STREAM, 
				NULL, 
				this->InputMediaType
			);
			if (hr == S_OK)
			{
				break;
			}
		}

		return hr;
	}

	bool VideoCapture::CreateSourceReaderAsync()
	{
		HRESULT hr;

		HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (hEvent == NULL)
		{
			MFUtil::ShowMessage(TEXT("CreateEvent Failed."), ML_ERROR);
			return false;
		}

		this->CallBack = new SourceReaderCallBack(hEvent);
		if (this->CallBack == NULL)
		{
			MFUtil::ShowMessage(TEXT("CreateCallBack Failed."), ML_ERROR);
			return false;
		}
	
		IMFAttributes *pAttributes = NULL;

		hr = MFCreateAttributes(&pAttributes, 1);
		if (hr != S_OK)
		{
			MFUtil::ShowMessage(TEXT("CreateAttributes Failed."), ML_ERROR);
			this->ReleaseDevices();
			return false;
		}

		hr = pAttributes->SetUnknown(MF_SOURCE_READER_ASYNC_CALLBACK, this->CallBack);
		if (hr != S_OK)
		{
			MFUtil::ShowMessage(TEXT("AttributeSetting Failed."), ML_ERROR);
			this->ReleaseDevices();
			return false;
		}

		pin_ptr<IMFSourceReader *> pSourceReader = &(this->SourceReader);
		hr = MFCreateSourceReaderFromMediaSource(this->Source, pAttributes, pSourceReader);
		if (hr != S_OK)
		{
			MFUtil::ShowMessage(TEXT("CreateSourceReader Failed."), ML_ERROR);
			this->ReleaseDevices();
			return false;
		}

		hr = this->ConfigureSourceReader();
		if (hr != S_OK)
		{
			MFUtil::ShowMessage(TEXT("ConfigureDecoder Failed."), ML_ERROR);
			MFUtil::ShowErrorNameFromCode(hr);
			return false;
		}

		// 二回目以降の ReadSample() はコールバック内で呼ぶため、
		// SourceReaderCallBack クラスにも SourceReader が必要。
		this->CallBack->SourceReader = this->SourceReader;

		return true;
	}

	bool VideoCapture::CreateCapture()
	{
		HRESULT hr = S_OK; 
		bool ret = false;

		ret = this->CreateMediaSource();
		if (!ret)
		{
			return false;
		}

		ret = this->CreateSourceReaderAsync();
		if (!ret)
		{
			return false;
		}

		return true;
	}

	bool VideoCapture::StartCapture()
	{
		HRESULT hr = NULL;

		this->CallBack->ReadStart();
		hr = this->SourceReader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, NULL, NULL, NULL, NULL);
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return false;
		}
		return true;
	}

	bool VideoCapture::StopCapture()
	{
		this->CallBack->ReadEnd();

		return true;
	}

	void VideoCapture::ReleaseDevices()
	{
		for (DWORD i = 0; i < this->DeviceCount; i++) 
		{ 
			this->Devices[i]->Release(); 
		} 
		CoTaskMemFree(this->Devices); 
		this->Source->Release();
		this->Source = NULL;
	}
}
