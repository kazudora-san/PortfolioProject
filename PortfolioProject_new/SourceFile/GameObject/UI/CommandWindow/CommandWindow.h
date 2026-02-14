#ifndef		COMMANDWINDOW_H
#define		COMMANDWINDOW_H

#include	"UI.h"
#include	<vector>

class CommandCursor;

class CommandWindow : public UI
{
private:
	CommandCursor*	m_Cursor	= nullptr;

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;
};

#endif