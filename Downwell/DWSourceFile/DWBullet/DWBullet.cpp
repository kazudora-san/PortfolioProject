//-----------------------------
//	DWBullet.cpp[弾の処理]
//	千葉知輝
//	作成日 2025/10/16
//-----------------------------

#include "DWBullet.h"
#include "DWMain.h"

constexpr DWVector2 BulletPosition = { 0.0f, 0.0f };

void DWBullet::Init()
{
	Scale = BulletScale;
	Position = BulletPosition;
	Tag = "Bullet";

	Collider = AddComponent<DWBoxCollider>(this);
	if (!Collider)
	{
		return;
	}

	// Component→継承したクラスのInitが呼ばれるので、Init()は不要
	RegistPendingComponent();

	Texture = LoadGraph("asset\\texture\\Bullet\\Bullet.png");
}

void DWBullet::Uninit()
{
	DWGameObject::Uninit();
}

void DWBullet::Update()
{
	if (!bEnable)
	{
		return;
	}

	DWGameObject::Update();

	Position += MoveSpeed;

	Life--;

	if (Life <= 0)
	{
		SetEnable(false);
	}
}

void DWBullet::Draw() const
{
	DWGameObject::Draw();
}

void DWBullet::SetEnable(bool enable)
{
	if(!bEnable && enable)
	{
		Life = BulletLife;
	}

	DWGameObject::SetEnable(enable);
}

void DWBullet::Reset()
{
	Position = BulletPosition;
	Life = BulletLife;
	SetEnable(false);
	SetActive(false);
}

void DWBullet::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
	if (!gameObject)
	{
		return;
	}

	// BulletかPlayerなら弾を消さない
	if (gameObject->GetTag() == "Bullet" ||
		gameObject->GetTag() == "Player")
	{
		return;
	}

	SetEnable(false);
}