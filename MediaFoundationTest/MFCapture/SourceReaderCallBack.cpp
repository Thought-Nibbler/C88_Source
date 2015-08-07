#include "stdafx.h"
#include "SourceReaderCallBack.h"

namespace MFCapture
{
	SourceReaderCallBack::SourceReaderCallBack(HANDLE hEvent) : m_nRefCount(1), m_hEvent(hEvent), m_bEOS(FALSE), m_hrStatus(S_OK)
	{
		InitializeCriticalSection(&m_critsec);

		HRESULT hr;
		this->CreateSinkWriter(240 * 1000, 640, 480, 30);
		this->IsCapture = false;
		this->IsFirstFrame = true;
	}

	SourceReaderCallBack::~SourceReaderCallBack() 
	{
	}

	HRESULT SourceReaderCallBack::CreateInMediaType(UINT32 bitrate, UINT32 width, UINT32 height, UINT32 fps)
	{
		HRESULT hr;

        hr = MFCreateMediaType(&(this->InMediaType));   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

        hr = this->InMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		// MFCapture::CreateInputMediaType() ‚Ì subtype ‚É‡‚í‚¹‚é‚±‚Æ
		hr = this->InMediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_YUY2);     
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

        hr = this->InMediaType->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		hr = MFSetAttributeSize(this->InMediaType, MF_MT_FRAME_SIZE, width, height);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		hr = MFSetAttributeRatio(this->InMediaType, MF_MT_FRAME_RATE, fps, 1);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

        hr = MFSetAttributeRatio(this->InMediaType, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		return hr;
	}

	HRESULT SourceReaderCallBack::CreateOutMediaType(UINT32 bitrate, UINT32 width, UINT32 height, UINT32 fps)
	{
		HRESULT hr;

		hr = MFCreateMediaType(&(this->OutMediaType));
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		hr = this->OutMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		hr = this->OutMediaType->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

	    hr = this->OutMediaType->SetUINT32(MF_MT_AVG_BITRATE, bitrate);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		hr = this->OutMediaType->SetUINT32(MF_MT_INTERLACE_MODE, MFVideoInterlace_Progressive);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		hr = MFSetAttributeSize(this->OutMediaType, MF_MT_FRAME_SIZE, width, height);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		hr = MFSetAttributeRatio(this->OutMediaType, MF_MT_FRAME_RATE, fps, 1);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		hr = MFSetAttributeRatio(this->OutMediaType, MF_MT_PIXEL_ASPECT_RATIO, 1, 1);   
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return hr;
		}

		return hr;
	}

	void SourceReaderCallBack::CreateSinkWriter(UINT32 bitrate, UINT32 width, UINT32 height, UINT32 fps)
	{
		HRESULT hr;
		
		pin_ptr<IMFSinkWriter *> pWriter = &(this->Writer);
		hr = MFCreateSinkWriterFromURL(L"output.mp4", NULL, NULL, pWriter);
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return;
		}

		hr = this->CreateOutMediaType(bitrate, width, height, fps);
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return;
		}

		hr = this->Writer->AddStream(this->OutMediaType, &(this->WriteStreamIdx));
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return;
		}

		hr = this->CreateInMediaType(bitrate, width, height, fps);
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return;
		}

		hr = MFTRegisterLocalByCLSID(
            __uuidof(CColorConvertDMO),
            MFT_CATEGORY_VIDEO_PROCESSOR,
            L"",
            MFT_ENUM_FLAG_SYNCMFT,
            0,
            NULL,
            0,
            NULL
        );
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return;
		}

		hr = this->Writer->SetInputMediaType(this->WriteStreamIdx, InMediaType, NULL);  
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return;
		}

		hr = this->Writer->BeginWriting();
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
			return;
		}
	}

	HRESULT SourceReaderCallBack::Wait(DWORD dwMilliseconds, BOOL *pbEOS)
	{
		*pbEOS = FALSE;

		DWORD dwResult = WaitForSingleObject(m_hEvent, dwMilliseconds);
		if (dwResult == WAIT_TIMEOUT)
		{
			return E_PENDING;
		}
		else if (dwResult != WAIT_OBJECT_0)
		{
			return HRESULT_FROM_WIN32(GetLastError());
		}

		*pbEOS = m_bEOS;
		return m_hrStatus;
	}

	bool SourceReaderCallBack::ReadStart()
	{
		EnterCriticalSection(&m_critsec);
		this->IsCapture = true;
	    LeaveCriticalSection(&m_critsec);
		MFUtil::ShowMessage(TEXT("ReadStart()"), ML_DEBUG);

		return true;
	}

	bool SourceReaderCallBack::ReadEnd()
	{
		EnterCriticalSection(&m_critsec);
		this->IsCapture = false;
	    LeaveCriticalSection(&m_critsec);
		MFUtil::ShowMessage(TEXT("ReadEnd()"), ML_DEBUG);

		return true;
	}

	/////////////////////////////////////////
	/// IMFSourceReaderCallback methods
	/////////////////////////////////////////
	HRESULT SourceReaderCallBack::OnReadSample(HRESULT hrStatus, DWORD /*dwStreamIndex*/, DWORD /*dwStreamFlags*/, LONGLONG timeStamp, IMFSample *pSample)
	{
		EnterCriticalSection(&m_critsec);

		if (FAILED(hrStatus))
		{
			MFUtil::ShowErrorNameFromCode(hrStatus);
			return hrStatus;
		}

		if (pSample)
		{
			if (this->IsFirstFrame)
			{
				this->BaseTime = timeStamp;
				this->IsFirstFrame = false;
			}

			TCHAR tempStr[1024];
			float secTime = ((float)(timeStamp - this->BaseTime)) / (10000000.0f);
			_stprintf(tempStr, L"Frame @ %08.3f[sec]", secTime);
			MFUtil::ShowMessage(tempStr, ML_DEBUG);

			pSample->SetSampleTime(timeStamp - this->BaseTime);
			this->Writer->WriteSample(this->WriteStreamIdx, pSample);
			if (!(this->IsCapture))
			{
				this->Writer->Finalize();
				LeaveCriticalSection(&m_critsec);
				SetEvent(m_hEvent);
				MFUtil::ShowMessage(TEXT("Finalize"), ML_DEBUG);
				return S_OK;
			}
		}
		HRESULT hr = this->SourceReader->ReadSample(
			(DWORD)MF_SOURCE_READER_FIRST_VIDEO_STREAM,
			0,
			NULL, 
			NULL, 
			NULL, 
			NULL 
        );
		if (hr != S_OK)
		{
			MFUtil::ShowErrorNameFromCode(hr);
		}

		m_hrStatus = hrStatus;

		LeaveCriticalSection(&m_critsec);
		SetEvent(m_hEvent);
		return S_OK;
	}

	STDMETHODIMP SourceReaderCallBack::OnEvent(DWORD, IMFMediaEvent *)
	{
		return S_OK;
	}

	STDMETHODIMP SourceReaderCallBack::OnFlush(DWORD)
	{
		return S_OK;
	}


	/////////////////////////////////////////
	/// IUnknown methods
	/////////////////////////////////////////
	STDMETHODIMP SourceReaderCallBack::QueryInterface(REFIID iid, void** ppv)
	{
		static const QITAB qit[] =
		{
			QITABENT(SourceReaderCallBack, IMFSourceReaderCallback),
			{ 0 },
		};
		return QISearch(this, qit, iid, ppv);
	}

	STDMETHODIMP_(ULONG) SourceReaderCallBack::AddRef()
	{
		return InterlockedIncrement(&m_nRefCount);
	}

	STDMETHODIMP_(ULONG) SourceReaderCallBack::Release()
	{
		ULONG uCount = InterlockedDecrement(&m_nRefCount);
		if (uCount == 0)
		{
			delete this;
		}
		return uCount;
	}
}