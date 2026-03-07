//-----------------------------
//	DWPlayerHealthUI.cpp[プレイヤーの残ライフ表示処理]
//	千葉知輝
//	作成日 2025/10/29
//-----------------------------

#include "DWMain.h"
#include "DWPlayerHealthUI.h"

constexpr DWVector2 PlayerHealthUIScale = { 50.0f, 50.0f };
constexpr DWVector2 PlayerHealthUIPosition = {200, 0.0f};

void DWPlayerHealthUI::Init()
{
	DWPlayerUI::Init();

	Scale = PlayerHealthUIScale;
	Position = PlayerHealthUIPosition;
	Tag = "PlayerHealthUI";

	Texture = LoadGraph("asset\\texture\\UI\\PlayerHealthIcon.png");
}

void DWPlayerHealthUI::Uninit()
{
	DWPlayerUI::Uninit();
}

void DWPlayerHealthUI::Update()
{
	if (!OwnerObject)
	{
		return;
	}

	DWPlayerUI::Update();

	PlayerHealth = OwnerObject->GetHealth();
}

void DWPlayerHealthUI::Draw() const
{
	for (int i = 0; i < PlayerHealth; i++)
	{
		const DWVector2 position = { Position.x + i * Scale.x, Position.y};

		DrawExtendGraph(static_cast<int>(position.x),
						static_cast<int>(position.y),
						static_cast<int>(position.x + Scale.x),
						static_cast<int>(position.y + Scale.y), Texture, TRUE);
	}
}

void DWPlayerHealthUI::Reset()
{
	PlayerHealth = 0;
}
