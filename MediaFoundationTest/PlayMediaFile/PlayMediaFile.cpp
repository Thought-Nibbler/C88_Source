// これは メイン DLL ファイルです。

#include "stdafx.h"
#include "msclr/marshal.h"
#include "mfplay.h"
#include "PlayMediaFile.h"

using namespace msclr::interop;

namespace PlayMediaFile
{
	Player::Player()
	{

	}

	bool Player::Play()
	{
		if (!(this->IsReady))
		{
			return false;
		}

		HRESULT hr = this->MFPlayer->Play();

		return (hr == S_OK);
	}

	bool Player::Pause()
	{
		if (!(this->IsReady))
		{
			return false;
		}

		HRESULT hr = this->MFPlayer->Pause();

		return (hr == S_OK);
	}

	bool Player::Stop()
	{
		if (!(this->IsReady))
		{
			return false;
		}

		HRESULT hr = this->MFPlayer->Stop();

		return (hr == S_OK);
	}

	VideoPlayer::VideoPlayer(IntPtr pHwnd, String^ fileName)
	{
		this->IsReady = false;
		this->MFPlayer = NULL;

		HWND hwnd = reinterpret_cast<HWND>(pHwnd.ToPointer());

		pin_ptr<IMFPMediaPlayer *> pMFPlayer = &(this->MFPlayer);

		marshal_context^ context = gcnew marshal_context;

		HRESULT hr = MFPCreateMediaPlayer(
			context->marshal_as<LPCWSTR>(fileName),
			FALSE,                                 
			0,
			NULL,
			hwnd,
			pMFPlayer
			);

		delete context;

		this->IsReady = (hr == S_OK);
	}

	AudioPlayer::AudioPlayer(String^ fileName)
	{
		this->IsReady = false;
		this->MFPlayer = NULL;

		pin_ptr<IMFPMediaPlayer *> pMFPlayer = &(this->MFPlayer);

		marshal_context^ context = gcnew marshal_context;

		HRESULT hr = MFPCreateMediaPlayer(
			context->marshal_as<LPCWSTR>(fileName),
			FALSE,                                 
			0,
			NULL,
			NULL,
			pMFPlayer
			);

		delete context;

		this->IsReady = (hr == S_OK);
	}
}