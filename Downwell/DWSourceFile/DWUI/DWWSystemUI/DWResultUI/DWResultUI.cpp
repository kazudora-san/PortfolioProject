//-----------------------------
//	DWResultUI.cpp[リザルトUI処理]
//	千葉知輝
//	作成日 2025/10/30
//-----------------------------

#include "DWResultUI.h"
#include "DWMain.h"
#include "DWSection/DWSection.h"
#include "DWInput/DWInput.h"
#include "DWScene/DWSceneManager.h"
#include "DWScene/DWTitleScene/DWTitleScene.h"

constexpr DWVector2 ResultBackGroundScale = { 800.0f, 600.0f };
constexpr DWVector2 ResultUIPosition = { 600.0f, ScreenResolutionHeight / 4.0f };
constexpr int ResultTextType = 4;
const std::string ResultText[ResultTextType] = { "GAME OVER", "Level:", "RESTART:Space or RSHIFT", "Title:Enter"};
constexpr int LineSpacing = 2;

void DWResultUI::Init()
{
	Scale = ResultUIScale;
	Position = ResultUIPosition;
	Tag = "ResultUI";

	if (!Scene)
	{
		return;
	}

	//SetFontSize(ResultUIFontSize);
	StageManager = Scene->GetManager<DWStageManager>();
	Texture = LoadGraph("asset\\texture\\UI\\Result\\ResultBackGround.png");
}

void DWResultUI::Uninit()
{
	DWUI::Uninit();
}

void DWResultUI::Update()
{
	DWUI::Update();

	if (!bIsResultUI)
	{
		return;
	}

	DWInput* input = GetInput();

	if (!Scene || !input)
	{
		return;
	}

	if (input->GetTitleKeyDown())
	{
		DWSceneManager* sceneManager = Scene->GetSceneManager();
		if (!sceneManager)
		{
			return;
		}

		sceneManager->ChangeScene(new DWTitleScene(sceneManager, "Title"));
	}

	if (input->GetActionDown())
	{
		Scene->SetRestart();
		bIsResultUI = false;
	}
}

void DWResultUI::Draw() const
{
	if (!bIsResultUI)
	{
		return;
	}

	int fontSize = GetFontSize();

	DrawExtendGraph(static_cast<int>(Position.x - fontSize),
					static_cast<int>(Position.y - fontSize),
					static_cast<int>(Position.x + ResultBackGroundScale.x),
					static_cast<int>(Position.y + ResultBackGroundScale.y), Texture, FALSE);

	for (int i = 0; i < ResultTextType;i++)
	{
		DWVector2 position = Position;

		if (ResultText[i] == "GAME OVER")
		{
			position.x = Position.x + fontSize * ResultText[i].size() / 2.0f;
		}

		// 間隔を２行分開けて表示
		DrawString(static_cast<int>(position.x),
					static_cast<int>(position.y + (i * GetFontSize() * LineSpacing)),
					ResultText[i].c_str(), RedColor);

		if (ResultText[i] == "Level:")
		{
			DrawFormatString(static_cast<int>(Position.x + fontSize * (ResultText[i].size())),
								static_cast<int>(Position.y + (i * GetFontSize() * LineSpacing)),
								RedColor, "%d", StageNumber);
		}
	}
}

void DWResultUI::Reset()
{
	bIsResultUI = false;
}

void DWResultUI::ResultUIDisp()
{
	if (StageManager)
	{
		StageNumber = StageManager->GetCurrentStageNumber();
	}

	bIsResultUI = true;
}

void DWResultUI::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
}
