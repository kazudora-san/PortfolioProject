//-----------------------------
//	DWGameObject.cpp[ゲームオブジェクトーの制御]
//	千葉知輝
//	作成日 2025/10/02
//-----------------------------

#include "DWGameObject.h"
#include "DWScene/DWSceneManager.h"
#include "DWMain.h"

constexpr int CameraViewTop = -100;
constexpr int CameraViewBottom = 1200;

void DWGameObject::Uninit()
{
	for (auto* component : PendingComponentList)
	{
		if (!component)
		{
			continue;
		}

		component->Uninit();
		delete component;
		component = nullptr;
	}

	for (auto* component : ComponentList)
	{
		if (!component)
		{
			continue;
		}

		component->Uninit();
		delete component;
		component = nullptr;
	}

	DeleteGraph(Texture);
}

void DWGameObject::Update()
{
	if (!Scene)
	{
		return;
	}

	const DWVector2 offset = Scene->GetOffset();
	const DWVector2 position = { Position.x - offset.x, Position.y - offset.y };

	if (!bActive)
	{
		return;
	}

	if (position.y + Scale.y < CameraViewTop ||
		position.y > CameraViewBottom)
	{
		SetEnable(false);
		return;
	}
	else
	{
		SetEnable(true);
	}

	for (DWComponent* component : ComponentList)
	{
		// nullチェック
		if (!component)
		{
			continue;
		}

		component->Update();
	}
}

void DWGameObject::Draw() const
{
	if (!bEnable)
	{
		return;
	}

	if (!Scene)
	{
		return;
	}

	const DWVector2 offset = Scene->GetOffset();
	const DWVector2 position = { Position.x - offset.x, Position.y - offset.y };

	DrawExtendGraph(static_cast<int>(position.x),
					static_cast<int>(position.y),
					static_cast<int>(position.x + Scale.x),
					static_cast<int>(position.y + Scale.y), Texture, TRUE);
}

void DWGameObject::SetEnable(bool enable)
{
	if (bEnable == enable)
	{
		return;
	}

	bEnable = enable;

	for (DWComponent* component : ComponentList)
	{
		if (!component)
		{
			continue;
		}

		component->SetEnable(enable);
	}
}

DWInput* DWGameObject::GetInput() const
{
	if (!Scene)
	{
		return nullptr;
	}

	DWSceneManager* sceneManager = Scene->GetSceneManager();

	if (!sceneManager)
	{
		return nullptr;
	}

	return sceneManager->GetInput();
}