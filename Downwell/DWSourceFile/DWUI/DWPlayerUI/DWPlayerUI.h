//-----------------------------
//	PlayerUI.h[PlayerUIêßå‰]
//	êÁótímãP
//	çÏê¨ì˙ 2025/10/29
//-----------------------------

#ifndef DWPLAYERUI_H
#define DWPLAYERUI_H

#include "DWUI/DWUI.h"
#include "DWPlayer/DWPlayer.h"

class DWPlayerUI : public DWUI
{
protected:
	DWPlayer*	OwnerObject		= nullptr;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override = 0;

	virtual void	Reset()	override = 0;
};
#endif // PLAYER_H
