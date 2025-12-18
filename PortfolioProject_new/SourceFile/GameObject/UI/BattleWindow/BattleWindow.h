#ifndef		BATTLEWINDOW_H
#define		BATTLEWINDOW_H

#include	"UI.h"
#include	<vector>

class BattleCommandCursor;

class BattleWindow : public UI // åpè≥
{
private:
	BattleCommandCursor*	m_Cursor	= nullptr;

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;
};

#endif