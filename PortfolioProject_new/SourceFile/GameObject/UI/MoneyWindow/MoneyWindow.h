#ifndef		MONEYWINDOW_H
#define		MONEYWINDOW_H

#include	"UI.h"

class Polygon2D;

class MoneyWindow : public UI
{
private:

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;
};

#endif