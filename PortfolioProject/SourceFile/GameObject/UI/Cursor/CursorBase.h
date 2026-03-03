#ifndef		CURSORBASE_H
#define		CURSORBASE_H

#include	"UI.h"

constexpr XMFLOAT2	CursorScale = { 50.0f, 50.0f };

class CursorBase : public UI
{
protected:
	XMFLOAT2		m_CursorPosition	= {};
	XMFLOAT2		m_CursorMove		= {};
	unsigned int	m_SelectIndex		= {};
	const char*		m_CursorFileName	= {};
	
public:
	virtual void	Init()			override;
	virtual void	Uninit()		override;
	virtual void	Update()		override;
	virtual void	Draw()			override;
	virtual void	CursorMove()	= 0;
	virtual void	Select()		= 0;
};

#endif