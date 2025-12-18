#ifndef		UI_H
#define		UI_H

#include	"GameObject.h"
#include	<vector>

class Polygon2D;
class Player;

class UI : public GameObject
{
protected:
	Player*					m_OwnerObject	= {};
	std::vector<Polygon2D*>	m_UIWindows		= {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;
};

#endif