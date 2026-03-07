//-----------------------------
//	AmmoUI.h[プレイヤーの残弾数の表示制御]
//	千葉知輝
//	作成日 2025/10/29
//-----------------------------

#ifndef DWAMMOUI_H
#define DWAMMOUI_H

#include "DWUI/DWPlayerUI/DWPlayerUI.h"

class DWAmmoUI : public DWPlayerUI
{
private:
	int	CurrentAmmo = 0;
	int	MaxAmmo = 0;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	Reset()	override;
};
#endif // PLAYER_H
