//-----------------------------
//	DWNormalBlock.cpp[ブロック処理]
//	千葉知輝
//	作成日 2025/10/20
//-----------------------------

#include "DWNormalBlock.h"
#include "DWMain.h"

constexpr DWVector2 NormalBlockPosition = { 0.0f, 0.0f };
constexpr DWVector2 NormalBlockScale = { 100.0f, 100.0f };

void DWNormalBlock::Init()
{
	Position = NormalBlockPosition;
	Scale = NormalBlockScale;
	Tag = "NormalBlock";

	// コンポーネントの追加
	Collider = AddComponent<DWBoxCollider>(this);

	// Component→継承したクラスのInitが呼ばれるので、
	// Init()は不要
	RegistPendingComponent();

	Texture = LoadGraph("asset\\texture\\Block\\NormalBlock.png");
}

void DWNormalBlock::Uninit()
{
	DWBlockBase::Uninit();
}

void DWNormalBlock::Update()
{
	DWBlockBase::Update();
}

void DWNormalBlock::Draw() const
{
	DWBlockBase::Draw();
}

void DWNormalBlock::SetEnable(bool enable)
{
	DWBlockBase::SetEnable(enable);
}

void DWNormalBlock::Reset()
{
	Position = NormalBlockPosition;
	SetEnable(false);
	SetActive(false);
}

void DWNormalBlock::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
}
