//-----------------------------
//	DWStageManager.h[DWStageManagerクラス制御]
//	千葉知輝
//	作成日 2025/10/24
//-----------------------------

#ifndef DWSTAGEMANAGER_H
#define DWSTAGEMANAGER_H

#include "DWManager/DWManager.h"
#include "DWSection/DWSection.h"
#include "DWUI/DWWSystemUI/DWCurrentStageUI/DWCurrentStageUI.h"
#include <vector>

class DWSection;

constexpr int MaxSection = 10;
constexpr int StageSection = 7;		// １ステージ分の区画
constexpr int MiddleSection = StageSection - 2;	// スタートとゴールを除いた分の区画数

class DWStageManager : public DWManager
{
private:
	std::vector<DWSection*> SectionList = {};
	bool	bStageViewFlag = true;
	bool	bRestartFlag	= false;
	unsigned int	CurrentStageNumber = 1;
	DWCurrentStageUI* CurrentStageUI = nullptr;

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;

	void	CurrentStageView();
	void	SetStageUI(DWCurrentStageUI* stageUI);
	void	ReStart() { bRestartFlag = true; }
	bool	GetReStartFlag() const { return bRestartFlag; }
	virtual void	Reset()		override;
	void	CreateStage();
	void	SpwanSection(int currentIndex, int sectionIndex, const DWVector2& offset);

	int		GetCurrentStageNumber()	const	{ return CurrentStageNumber; }
};

#endif // DWSTAGEMANAGER_H