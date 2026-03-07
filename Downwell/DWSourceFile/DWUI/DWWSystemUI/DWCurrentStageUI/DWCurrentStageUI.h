//-----------------------------
//	CurrentStageUI.h[CurrentStageUIêßå‰]
//	êÁótímãP
//	çÏê¨ì˙ 2025/10/29
//-----------------------------

#ifndef DWCURRENTSTAGEUI_H
#define DWCURRENTSTAGEUI_H

#include "DWUI/DWUI.h"

constexpr int StageUIFontSize = 60;

class DWCurrentStageUI : public DWUI
{
private:
	int				StageNumber		= 0;
	unsigned int	Color			= -1;
	bool			DispFlag		= false;
	const int		DispFrame		= 180;
	int				CurrentFrame	= 0;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	Reset()	override;
	void	CurrentStageDispFlag(int stageNumber);
};
#endif // PLAYER_H
