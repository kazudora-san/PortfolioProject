//-----------------------------
//	PlayerHealthUI.h[プレイヤーの残ライフ制御]
//	千葉知輝
//	作成日 2025/10/29
//-----------------------------

#ifndef DWPLAYERHEALTHUI_H
#define DWPLAYERHEALTHUI_H

#include "DWUI/DWPlayerUI/DWPlayerUI.h"

class DWPlayerHealthUI : public DWPlayerUI
{
private:
	float	PlayerHealth = 0;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	Reset()	override;
};
#endif // PLAYER_H
