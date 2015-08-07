// MFUtil.h
// http://blog.firefly-vj.net/2009/09/09/mediafoundation-hresult-pretty-print.html
//
#pragma once
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

namespace MFCapture
{
	struct ErrorTable
	{
		HRESULT Code;
		TCHAR Description[384];
		TCHAR Name[64];
	};

	public enum MessageLevel
	{
		ML_DEBUG,
		ML_INFO,
		ML_WARN,
		ML_ERROR
	};

	static class MFUtil
	{
	private:
		static const ErrorTable MFErrorTable[281];
	public:
		static void ShowErrorNameFromCode(HRESULT code);
		static void ShowErrorDescriptionFromCode(HRESULT code);
		static void ShowMessage(LPCTSTR message, MessageLevel ml);
	};

}