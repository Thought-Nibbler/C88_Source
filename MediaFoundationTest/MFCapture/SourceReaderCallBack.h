// SourceReaderCallBack.h

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

namespace MFCapture
{
	public class SourceReaderCallBack : public IMFSourceReaderCallback
	{
	public:
		IMFSourceReader *SourceReader;
	public:
		SourceReaderCallBack(HANDLE hEvent);
		HRESULT Wait(DWORD dwMilliseconds, BOOL *pbEOS);
		bool ReadStart();
		bool ReadEnd();

		/////////////////////////////////////////
		/// IUnknown methods
		/////////////////////////////////////////
		STDMETHODIMP QueryInterface(REFIID iid, void** ppv);
		STDMETHODIMP_(ULONG) AddRef();
		STDMETHODIMP_(ULONG) Release();

		/////////////////////////////////////////
		/// IMFSourceReaderCallback methods
		/////////////////////////////////////////
		STDMETHODIMP OnReadSample(
			HRESULT    hrStatus, 
			DWORD      dwStreamIndex, 
			DWORD      dwStreamFlags, 
			LONGLONG   llTimestamp, 
			IMFSample  *pSample
		);
		STDMETHODIMP OnEvent(DWORD, IMFMediaEvent *);
		STDMETHODIMP OnFlush(DWORD);
	private:
		long                m_nRefCount; 
		CRITICAL_SECTION    m_critsec;
		HANDLE              m_hEvent;
		BOOL                m_bEOS;
		HRESULT             m_hrStatus;
		IMFMediaSink        *MediaSink;
		IMFSinkWriter       *Writer;
		DWORD               WriteStreamIdx;
		bool                IsCapture;
		bool                IsFirstFrame;
		LONGLONG            BaseTime;
		IMFMediaType        *InMediaType;
		IMFMediaType        *OutMediaType;
	private:
		virtual ~SourceReaderCallBack();
		HRESULT CreateInMediaType(UINT32 bitrate, UINT32 width, UINT32 height, UINT32 fps);
		HRESULT CreateOutMediaType(UINT32 bitrate, UINT32 width, UINT32 height, UINT32 fps);
		void CreateSinkWriter(UINT32 bitrate, UINT32 width, UINT32 height, UINT32 fps);
	};
}
