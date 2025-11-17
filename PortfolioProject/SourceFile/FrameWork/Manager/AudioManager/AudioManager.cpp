#include	"Main.h"
#include	"Audio/Audio.h"
#include	"Manager/AudioManager/AudioManager.h"

std::unordered_map<std::string, Audio*> AudioManager::m_Audios;

void AudioManager::Init()
{
	Audio::InitMaster();
}

void AudioManager::Uninit()
{
	for (auto& pair : m_Audios)
	{
		pair.second->Uninit();
		delete pair.second;
	}
	m_Audios.clear();

	Audio::UninitMaster();
}

void AudioManager::Load(const char* fileName, const std::string& key)
{
	Audio* audio = new Audio(nullptr);
	audio->Load(fileName);
	m_Audios[key] = audio;
}

void AudioManager::Play(const std::string& key, bool loop)
{
	if (m_Audios.count(key))
	{
		m_Audios[key]->Play(loop);
	}
}

void AudioManager::Stop(const std::string& key)
{
	if (m_Audios.count(key))
	{
		// Audio ‘¤‚É Stop ŽÀ‘•‚·‚é
		m_Audios[key]->Stop();
	}
}
