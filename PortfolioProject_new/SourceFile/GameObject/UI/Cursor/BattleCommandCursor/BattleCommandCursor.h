#ifndef		BATTLECOMMANDCURSOR_H
#define		BATTLECOMMANDCURSOR_H

#include	"Cursor/CursorBase.h"

class BattleCommandCursor : public CursorBase
{
private:
	
public:
	virtual void	Init()			override;
	virtual void	Uninit()		override;
	virtual void	Update()		override;
	virtual void	Draw()			override;
	virtual void	CursorMove()	override;
	virtual void	Select()		override;
};

#endif