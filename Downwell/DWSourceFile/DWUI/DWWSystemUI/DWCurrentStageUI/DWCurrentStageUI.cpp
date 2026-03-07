//-----------------------------
//	DWCurrentStageUI.cpp[CurrentStageUI処理]
//	千葉知輝
//	作成日 2025/10/29
//-----------------------------

#include "DWMain.h"
#include "DWCurrentStageUI.h"
#include "DWManager/DWStageManager/DWStageManager.h"

constexpr DWVector2 StageUIPosition = { ScreenResolutionWidth / 2.0f, ScreenResolutionHeight / 4.0f };

void DWCurrentStageUI::Init()
{
	DWUI::Init();

	Position = StageUIPosition;
	SetFontSize(StageUIFontSize);
	Color = GetColor(255, 255, 255);
	Tag = "CurrentStageUI";

	DWStageManager* stageManager = Scene->GetManager<DWStageManager>();
	if (!stageManager)
	{
		return;
	}

	stageManager->SetStageUI(this);
}

void DWCurrentStageUI::Uninit()
{
	DWUI::Uninit();
}

void DWCurrentStageUI::Update()
{
	DWUI::Update();

	if (CurrentFrame > DispFrame)
	{
		DispFlag = false;
		return;
	}

	CurrentFrame++;
}

void DWCurrentStageUI::Draw() const
{
	if (!DispFlag)
	{
		return;
	}

	DrawFormatString(static_cast<int>(Position.x),
						static_cast<int>(Position.y),
						Color, "ステージ %d", StageNumber);
}

void DWCurrentStageUI::Reset()
{
}

void DWCurrentStageUI::CurrentStageDispFlag(int stageNumber)
{
	if (DispFlag)
	{
		return;
	}

	DispFlag = true;
	CurrentFrame = 0;
	StageNumber = stageNumber;
}
