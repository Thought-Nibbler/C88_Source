// PlayMediaFile.h

#pragma once

using namespace System;

namespace PlayMediaFile 
{
	//////////////////////////////////////////
	/// メディアファイル再生管理クラス
	//////////////////////////////////////////
	public ref class Player
	{
	protected:
		// 実際のMFPlayインターフェイス
		IMFPMediaPlayer *MFPlayer;

		// 再生（停止）の準備ができているかどうか
		bool IsReady;

	public:
		// コンストラクタ
		Player();

		// 再生
		bool Play();

		// 一時停止
		bool Pause();

		// 停止
		bool Stop();
	};

	//////////////////////////////////////////
	/// 動画ファイル再生管理クラス
	//////////////////////////////////////////
	public ref class VideoPlayer : Player
	{
	public:
		// コンストラクタ
		VideoPlayer(IntPtr pHwnd, String^ fileName);
	};

	//////////////////////////////////////////
	/// 音声ファイル再生管理クラス
	//////////////////////////////////////////
	public ref class AudioPlayer : Player
	{
	public:
		// コンストラクタ
		AudioPlayer(String^ fileName);
	};
}
