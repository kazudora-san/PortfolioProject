#ifndef		COMMANDWINDOW_H
#define		COMMANDWINDOW_H

#include	"UI.h"
#include	<vector>

class Cursor;

class CommandWindow : public UI // åpè≥
{
private:
	Cursor*	m_Cursor	= nullptr;

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;
};

#endif