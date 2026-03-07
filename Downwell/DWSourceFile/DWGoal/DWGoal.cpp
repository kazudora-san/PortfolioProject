//-----------------------------
//	DWGoal.cpp[ゴール処理]
//	千葉知輝
//	作成日 2025/10/28
//-----------------------------

#include "DWGoal.h"

constexpr DWVector2 GoalPosition = { FieldOffset.x,
SectionHeight * TileSize.y * StageSection - GoalScale.y + FieldOffset.y };

void DWGoal::Init()
{
	Scale = GoalScale;
	Position = GoalPosition;
	Tag = "Goal";

	Collider = AddComponent<DWBoxCollider>(this);
	if (!Collider)
	{
		return;
	}

	// Component→継承したクラスのInitが呼ばれるので、Init()は不要
	RegistPendingComponent();
}

void DWGoal::Uninit()
{
	DWGameObject::Uninit();
}

void DWGoal::Update()
{
	DWGameObject::Update();
}

void DWGoal::Draw() const
{
}

void DWGoal::Reset()
{
	bIsGoal = false;
}

void DWGoal::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
	if (!gameObject)
	{
		return;
	}

	if (gameObject->GetTag() == "Player")
	{
		SetGoalFlag(true);
	}
}
