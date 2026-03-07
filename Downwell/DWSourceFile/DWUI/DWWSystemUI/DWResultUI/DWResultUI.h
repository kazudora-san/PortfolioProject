//-----------------------------
//	ResultUI.h[リザルトUI制御]
//	千葉知輝
//	作成日 2025/10/30
//-----------------------------

#ifndef DWRESULTUI_H
#define DWRESULTUI_H

#include "DWUI/DWUI.h"
#include "DWVector2/DWVector2.h"
#include "DWManager/DWStageManager/DWStageManager.h"
#include "DWMain.h"
#include <string>

constexpr DWVector2 ResultUIScale = { 500.0f, 500.0f };

class DWResultUI : public DWUI
{
private:
	bool	bIsResultUI = false;
	DWStageManager* StageManager = nullptr;
	int			StageNumber	= 0;
	const int	RedColor	= GetColor(255, 0, 0);

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	Reset() override;
	void ResultUIDisp();
	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};
#endif // PLAYER_H
