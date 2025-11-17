#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

class Audio;

class AudioManager
{
private:
	static std::unordered_map<std::string, Audio*> m_Audios;

public:
	static void Init	();
	static void Uninit	();
	static void Load	(const char*		fileName,	const std::string&	key);
	static void Play	(const std::string&	ke,			bool				oop = false);
	static void Stop	(const std::string&	key);
};

#endif // AUDIOMANAGER_H