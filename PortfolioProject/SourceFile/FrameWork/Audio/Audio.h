#pragma once

#include	"Component/Component.h"
#include	<xaudio2.h>
#include	<unordered_map>
#include	<string>


class Audio : public Component
{
private:
	int m_Length = {};
	int m_PlayLength = {};

	static IXAudio2* m_Xaudio;
	static IXAudio2MasteringVoice* m_MasteringVoice;

	IXAudio2SourceVoice* m_SourceVoice = {};

	BYTE* m_SoundData = {};

public:
	static void InitMaster();
	static void UninitMaster();

	using Component::Component;

	void Uninit();
	void Load(const char* FileName);
	void Play(bool Loop = false);
	void Stop();

	// É{ÉäÉÖÅ[ÉÄí≤êÆ
	void SetVolume(float volume);
};