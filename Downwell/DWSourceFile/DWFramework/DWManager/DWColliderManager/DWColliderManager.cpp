//-----------------------------
//	DWColliderManager.cpp[弾管理クラスの処理]
//	千葉知輝
//	作成日 2025/10/17
//-----------------------------

#define NOMINMAX #include <Windows.h> #include <algorithm>

#include "DWColliderManager.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"
#include <algorithm>

void DWColliderManager::Init()
{

}

void DWColliderManager::Uninit()
{
	ColliderObjectList.clear();
}

void DWColliderManager::Update()
{
	for (int i = 0; i < ColliderObjectList.size(); i++)
	{
		ColliderObjectList[i]->SetHitFlagY(false);
	}

	// BoxColliderを持ったEnableがtrueのオブジェクトの当たり判定を調べる
	for (int i = 0; i < ColliderObjectList.size(); i++)
	{
		DWGameObject* gameObjectA = ColliderObjectList[i]->GetGameObject();
		if (!gameObjectA)
		{
			continue;
		}

		if (!ColliderObjectList[i]->IsActive())
		{
			continue;
		}

		ColliderObjectList[i]->SetBoxPosition({ gameObjectA->GetPosition() });
		
		for (int j = i + 1; j < ColliderObjectList.size(); j++)
		{
			DWGameObject* gameObjectB = ColliderObjectList[j]->GetGameObject();
			if (!gameObjectB)
			{
				continue;
			}

			if (!ColliderObjectList[j]->IsActive())
			{
				continue;
			}

			ColliderObjectList[j]->SetBoxPosition({ gameObjectB->GetPosition() });

			if (BoundingBox(ColliderObjectList[i], ColliderObjectList[j]))
			{
				gameObjectA->OnCollision(gameObjectB, ColliderObjectList[i]->GetOverlap());
				gameObjectB->OnCollision(gameObjectA, ColliderObjectList[j]->GetOverlap());
			}

			if (!gameObjectA->GetEnable())
			{
				break;
			}
		}
	}
}

bool DWColliderManager::PushColliderObject(DWBoxCollider* colliderObject)
{
	if (!colliderObject)
	{
		return false;
	}

	colliderObject->SetHitFlagY(false);
	colliderObject->SetOverlap({ 0.0f, 0.0f });
	ColliderObjectList.push_back(colliderObject);
	return true;
}

bool DWColliderManager::BoundingBox(DWBoxCollider* objectA, DWBoxCollider* objectB)
{
	if (!objectA || !objectB)
	{
		return false;
	}

	const DWVector2& positionA = objectA->GetBoxPosition();
	const DWVector2& scaleA = objectA->GetScale();

	float topA = positionA.y;
	float bottomA = positionA.y + scaleA.y;
	float leftA = positionA.x;
	float rightA = positionA.x + scaleA.x;

	const DWVector2& positionB = objectB->GetBoxPosition();
	const DWVector2& scaleB = objectB->GetScale();

	float topB = positionB.y;
	float bottomB = positionB.y + scaleB.y;
	float leftB = positionB.x;
	float rightB = positionB.x + scaleB.x;

	if (topA > bottomB || bottomA < topB)
	{
		return false;
	}

	if (rightA < leftB || leftA > rightB)
	{
		return false;
	}

	float overlapX = std::min(rightA, rightB) - std::max(leftA, leftB);
	float overlapY = std::min(bottomA, bottomB) - std::max(topA, topB);

	objectA->SetOverlap({ overlapX, overlapY });
	objectB->SetOverlap({ overlapX, overlapY });

	return true;
}
