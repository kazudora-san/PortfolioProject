#ifndef AUDIO_H
#define AUDIO_H



#include "Component/Component.h"
#include <xaudio2.h>
#include <unordered_map>
#include <string>


class Audio : public Component
{
private:
	int								m_Length		= {};
	int								m_PlayLength	= {};

	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	IXAudio2SourceVoice*			m_SourceVoice	= {};
	BYTE*							m_SoundData		= {};

public:
	static void InitMaster	();
	static void UninitMaster();

	using Component::Component;

	void	Uninit		();

	void	Load		(const char *FileName);
	void	Play		(bool Loop = false);

	// ストップの機能を追加
	void	Stop		()
	{
		if (m_SourceVoice)
		{
			m_SourceVoice->Stop(0);
			m_SourceVoice->FlushSourceBuffers();
		}
	}

	// ボリューム調整を追加
	void	SetVolume	(float volume)
	{
		if (m_SourceVoice)
		{
			m_SourceVoice->SetVolume(volume);
		}
	}

	// 3Dサウンド（立体音響）
	// 左から聞こえたり、右から聞こえたりなど

};

#endif // !AUDIO_H