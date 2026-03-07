//-----------------------------
//	DWAmmoUI.cpp[プレイヤーの残弾数の表示処理]
//	千葉知輝
//	作成日 2025/10/29
//-----------------------------

#include "DWMain.h"
#include "DWAmmoUI.h"
#include "DWPlayer/DWPlayer.h"

constexpr DWVector2 AmmoUIScale = { 50.0f, 500.0f };
constexpr DWVector2 AmmoUIPosition = {1600.0f, ScreenResolutionHeight / 4 * 3};

void DWAmmoUI::Init()
{
	DWPlayerUI::Init();

	Scale = AmmoUIScale;
	Position = AmmoUIPosition;
	Tag = "AmmoUI";

	Texture = LoadGraph("asset\\texture\\UI\\AmmoIcon.png");
}

void DWAmmoUI::Uninit()
{
	DWPlayerUI::Uninit();
}

void DWAmmoUI::Update()
{
	if (!OwnerObject)
	{
		return;
	}

	DWPlayerUI::Update();

	CurrentAmmo = OwnerObject->GetCurrentAmmo();
	MaxAmmo = MaxAmmoCount;
}

void DWAmmoUI::Draw() const
{
	const DWVector2 scale = { Scale.x, Scale.y / MaxAmmo };
	
	for (int i = 0; i < CurrentAmmo; i++)
	{
		// i + 1はポジション調整(最初からスケール分引いていく)
		const DWVector2 position = { Position.x, Position.y - (i + 1) * scale.y };

		DrawExtendGraph(static_cast<int>(position.x),
						static_cast<int>(position.y),
						static_cast<int>(position.x + scale.x),
						static_cast<int>(position.y + scale.y), Texture, TRUE);
	}
}

void DWAmmoUI::Reset()
{
	CurrentAmmo = 0;
}
