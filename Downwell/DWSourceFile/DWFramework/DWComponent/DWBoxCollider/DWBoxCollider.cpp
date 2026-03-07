//-----------------------------
//	DWBoxCollider.cpp[当たり判定（AABB）の処理]
//	千葉知輝
//	作成日 2025/10/15
//-----------------------------

#include "DWBoxCollider.h"
#include "DWGameObject.h"
#include "DWManager/DWColliderManager/DWColliderManager.h"

DWBoxCollider::DWBoxCollider(DWGameObject* gameObject)
{
	if (!gameObject)
	{
		return;
	}

	OwnerObject = gameObject;
	BoundingBoxPosition = OwnerObject->GetPosition();
	BoundingBoxScale = OwnerObject->GetScale();
}

void DWBoxCollider::Init()
{
	if (!OwnerObject)
	{
		return;
	}

	DWScene* scene = OwnerObject->GetScene();
	if (!scene)
	{
		return;
	}

	DWColliderManager* colliderManager = scene->GetManager<DWColliderManager>();
	if (!colliderManager)
	{
		return;
	}

	colliderManager->PushColliderObject(this);
}

void DWBoxCollider::Uninit()
{
	DWComponent::Uninit();
}

void DWBoxCollider::Update()
{
	if (!bEnable)
	{
		return;
	}

	BoundingBoxPosition = OwnerObject->GetPosition();
}

void DWBoxCollider::SetEnable(bool enable)
{
	DWComponent::SetEnable(enable);

	if (!bEnable)
	{
		return;
	}

	BoundingBoxPosition = OwnerObject->GetPosition();
}
