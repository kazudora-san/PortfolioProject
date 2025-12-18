#ifndef		CURSORBASE_H
#define		CURSORBASE_H

#include	"UI.h"

constexpr XMFLOAT2	CursorScale = { 50.0f, 50.0f };

class CursorBase : public UI // åpè≥
{
protected:
	const char* m_CursorFileName	= {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;
};

#endif