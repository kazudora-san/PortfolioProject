#ifndef		RESULT_H
#define		RESULT_H

#include	"Scene/Scene.h"

class AudioManager;

class Result : public Scene
{
private:
	AudioManager*	m_Audio;
	unsigned int	m_Frame;

public:
	void	Init();
	void	Update();
};

#endif // RESULT_H