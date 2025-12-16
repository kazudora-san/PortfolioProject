#ifndef		TITLE_H
#define		TITLE_H

#include	"Scene/Scene.h"
#include	<string>

class AudioManager;
class AnimationModel;

class Title :public Scene
{
private:
	unsigned int		m_Frame				= {};
	unsigned int		m_StopFrame			= {};
	bool				m_IsNextScene		= {};

	AudioManager*		m_Audio				= {};

public:
	void	Init()		override;
	void	Update()	override;

};

#endif // !TITLE_H