// PlayMediaFile.h

#pragma once

using namespace System;

namespace PlayMediaFile 
{
	//////////////////////////////////////////
	/// ���f�B�A�t�@�C���Đ��Ǘ��N���X
	//////////////////////////////////////////
	public ref class Player
	{
	protected:
		// ���ۂ�MFPlay�C���^�[�t�F�C�X
		IMFPMediaPlayer *MFPlayer;

		// �Đ��i��~�j�̏������ł��Ă��邩�ǂ���
		bool IsReady;

	public:
		// �R���X�g���N�^
		Player();

		// �Đ�
		bool Play();

		// �ꎞ��~
		bool Pause();

		// ��~
		bool Stop();
	};

	//////////////////////////////////////////
	/// ����t�@�C���Đ��Ǘ��N���X
	//////////////////////////////////////////
	public ref class VideoPlayer : Player
	{
	public:
		// �R���X�g���N�^
		VideoPlayer(IntPtr pHwnd, String^ fileName);
	};

	//////////////////////////////////////////
	/// �����t�@�C���Đ��Ǘ��N���X
	//////////////////////////////////////////
	public ref class AudioPlayer : Player
	{
	public:
		// �R���X�g���N�^
		AudioPlayer(String^ fileName);
	};
}
