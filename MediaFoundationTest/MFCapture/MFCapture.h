// MFCapture.h

#pragma once
#include <stdio.h>
#include "mfapi.h"
#include "mfidl.h"
#include "mfplay.h"
#include "Mferror.h"
#include "mfreadwrite.h"
#include "shlwapi.h"
#include "wmcodecdsp.h"
#include "MFUtil.h"
#include "SourceReaderCallBack.h"

using namespace System;

namespace MFCapture 
{
	public ref class VideoCapture
	{
	private:
		IMFAttributes *Config; 
		IMFActivate **Devices; 
		UINT32 DeviceCount;
		IMFMediaSource *Source;
		IMFSourceReader *SourceReader;
		SourceReaderCallBack *CallBack;
		IMFMediaType *InputMediaType;

		HRESULT CreateInputMediaType(GUID majorType, GUID subtype);
		HRESULT ConfigureSourceReader();
		bool CreateSourceReaderAsync();
		bool CreateMediaSource();

		// �f�o�C�X���
		void ReleaseDevices();
	public:
		// �R���X�g���N�^
		VideoCapture();

		// �f�X�g���N�^
		~VideoCapture();

		bool CreateCapture();

		bool StartCapture();

		bool StopCapture();
	};

}
