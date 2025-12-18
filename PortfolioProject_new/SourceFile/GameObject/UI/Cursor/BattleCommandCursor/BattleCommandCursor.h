#ifndef		BATTLECOMMANDCURSOR_H
#define		BATTLECOMMANDCURSOR_H

#include	"Cursor/CursorBase.h"

class BattleCommandCursor : public CursorBase // åpè≥
{
private:
	
public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	void			Update()	override;
	virtual void	Draw()		override;
};

#endif