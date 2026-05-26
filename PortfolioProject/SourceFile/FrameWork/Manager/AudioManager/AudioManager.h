#pragma once

#include <unordered_map>
#include <string>

class Audio;

class AudioManager
{
private:
	static std::unordered_map<std::string, Audio*> m_Audios;

public:
	static void Init();
	static void Uninit();

	static void Load(const char* fileName, const std::string& key);
	static void Play(const std::string& key, bool loop = false);
	static void Stop(const std::string& key);
};