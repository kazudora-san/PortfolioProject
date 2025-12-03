#ifndef		GAME_H
#define		GAME_H

#include	"Scene/Scene.h"

class Game :public Scene
{
private:
	unsigned	int		m_StopFrame = 180;
	unsigned	int		m_NowFrame = 0;
public:
	void	Init()		override;
	void	Update()	override;
};

#endif // GAME_H