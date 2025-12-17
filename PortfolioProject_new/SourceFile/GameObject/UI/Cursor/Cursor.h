#ifndef		CURSOR_H
#define		CURSOR_H

#include	"UI.h"
#include	<vector>

class Polygon2D;

constexpr XMFLOAT2	CursorScale = { 50.0f, 50.0f };

class Cursor : public UI // åpè≥
{
private:

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;
};

#endif