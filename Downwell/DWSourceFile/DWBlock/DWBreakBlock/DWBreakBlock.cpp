//-----------------------------
//	DWBreakBlock.cpp[壊れるブロック処理]
//	千葉知輝
//	作成日 2025/10/30
//-----------------------------

#include "DWBreakBlock.h"
#include "DWMain.h"

constexpr DWVector2 BreakBlockPosition = { 0.0f, 0.0f };
constexpr DWVector2 BreakBlockScale = { 100.0f, 100.0f };

void DWBreakBlock::Init()
{
	Position = BreakBlockPosition;
	Scale = BreakBlockScale;
	Tag = "BreakBlock";

	// コンポーネントの追加
	Collider = AddComponent<DWBoxCollider>(this);

	// Component→継承したクラスのInitが呼ばれるので、
	// Init()は不要
	RegistPendingComponent();

	Texture = LoadGraph("asset\\texture\\Block\\BreakBlock.png");
}

void DWBreakBlock::Uninit()
{
	DWBlockBase::Uninit();
}

void DWBreakBlock::Update()
{
	if (BlockLife <= 0)
	{
		return;
	}

	DWBlockBase::Update();
}

void DWBreakBlock::Draw() const
{
	DWBlockBase::Draw();
}

void DWBreakBlock::SetEnable(bool enable)
{
	DWBlockBase::SetEnable(enable);
}

void DWBreakBlock::Reset()
{
	Position = BreakBlockPosition;
	SetEnable(false);
	SetActive(false);
	BlockLife = BreakBlockLife;
}

void DWBreakBlock::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
	if (!gameObject)
	{
		return;
	}

	if (gameObject->GetTag() == "Bullet")
	{
		BlockLife--;

		if (BlockLife <= 0)
		{
			SetEnable(false);
		}
	}
}
