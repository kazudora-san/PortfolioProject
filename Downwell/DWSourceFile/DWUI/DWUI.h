//-----------------------------
//	UI.h[UI§Œä]
//	ç—t’m‹P
//	ì¬“ú 2025/10/29
//-----------------------------

#ifndef DWUI_H
#define DWUI_H

#include "DWGameObject.h"

class DWUI : public DWGameObject
{
public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override = 0;

	virtual void	Reset()	override = 0;
};
#endif // PLAYER_H
