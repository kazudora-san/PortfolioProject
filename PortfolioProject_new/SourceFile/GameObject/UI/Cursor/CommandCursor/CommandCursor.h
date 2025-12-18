#ifndef		COMMANDCURSOR_H
#define		COMMANDCURSOR_H

#include	"Cursor/CursorBase.h"

class CommandCursor : public CursorBase // åpè≥
{
private:
	
public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;
};

#endif