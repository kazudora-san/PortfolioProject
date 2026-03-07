//-----------------------------
//	DWEnemy.cpp[エネミー処理]
//	千葉知輝
//	作成日 2025/10/21
//-----------------------------

#include "DWEnemyGround.h"
#include "DWMain.h"

constexpr int EnemyHealth = 4;

void DWEnemyGround::Init()
{
	Scale = EnemyScale;
	Position = EnemyPosition;
	Health = EnemyHealth;
	Velocity.y = GravityFactor;
	Tag = "EnemyGround";

	// コンポーネントの追加
	Collider = AddComponent<DWBoxCollider>(this);
	if (!Collider)
	{
		return;
	}

	Collider->SetEnable(false);

	// Component→継承したクラスのInitが呼ばれるので、
	// stateMachine->Init()は不要
	RegistPendingComponent();

	// 画像読み込み
	Texture = LoadGraph("asset\\texture\\Enemy\\enemyNormal.png");
}

void DWEnemyGround::Uninit()
{
	DWEnemyBase::Uninit();
}

void DWEnemyGround::Update()
{
	DWEnemyBase::Update();

	if (!bEnable)
	{
		return;
	}

	Position += Velocity;
}

void DWEnemyGround::Draw() const
{
	DWEnemyBase::Draw();
}

void DWEnemyGround::SetEnable(bool enable)
{
	DWEnemyBase::SetEnable(enable);
}

void DWEnemyGround::Reset()
{
	Position = EnemyPosition;
	Velocity.y = GravityFactor;
	Health = EnemyHealth;
	SetEnable(false);
	SetActive(false);
}

void DWEnemyGround::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
	if (!gameObject)
	{
		return;
	}

	if (gameObject->GetTag() == "Bullet")
	{
		Health--;

		if (Health <= 0)
		{
			SetEnable(false);
		}

		return;
	}

	if (gameObject->GetTag() == "NormalBlock" ||
		gameObject->GetTag() == "BreakBlock")
	{
		const DWVector2& pushOut = overlap;

		// めり込んだ分を押し出し
		if (pushOut.x < pushOut.y)
		{
			// X軸
			if (GetPosition().x < gameObject->GetPosition().x)
			{
				SetPosition({ Position.x - overlap.x, Position.y });
			}
			else
			{
				SetPosition({ Position.x + overlap.x, Position.y });
			}

			SetVelocity({ 0.0f, Velocity.y });
		}
		else
		{
			if (GetPosition().y < gameObject->GetPosition().y)
			{
				Velocity.y = 0.0f;
				SetPosition({ Position.x, Position.y - overlap.y });
			}
			else
			{
				SetPosition({ Position.x, Position.y + overlap.y });
			}
		}

		return;
	}
}
