//-----------------------------
//	DWScene.cpp[シーン処理]
//	千葉知輝
//	作成日 2025/10/10
//-----------------------------
#include "DWScene.h"
#include "DWManager/DWManager.h"
#include "DWManager/DWStageManager/DWStageManager.h"

void DWScene::Uninit()
{
	for (DWManager* manager : ManagerList)
	{
		if (!manager)
		{
			continue;
		}

		manager->Uninit();
		delete manager;
		manager = nullptr;
	}

	ManagerList.clear();

	for (int i = 0; i < LayerMax; i++)
	{
		for (DWGameObject* gameObject : GameObjectList[i])
		{
			if (!gameObject)
			{
				continue;
			}

			gameObject->Uninit();
			delete gameObject;
			gameObject = nullptr;
		}

		GameObjectList[i].clear();
	}
}

void DWScene::Update()
{
	for (DWManager* manager : ManagerList)
	{
		if (!manager)
		{
			continue;
		}

		manager->Update();
	}

	for (int i = 0; i < LayerMax; i++)
	{
		for (DWGameObject* gameObject : GameObjectList[i])
		{
			if (!gameObject)
			{
				continue;
			}

			gameObject->Update();
		}
	}

	RegistPendingGameObject();
}

void DWScene::Draw()
{
	for (int i = 0; i < LayerMax; i++)
	{
		for (DWGameObject* gameObject : GameObjectList[i])
		{
			if (!gameObject)
			{
				continue;
			}

			gameObject->Draw();
		}
	}
}

void DWScene::SetRestart()
{
	bRestartFlag = true;

	DWStageManager* stageManager = GetManager<DWStageManager>();
	if (!stageManager)
	{
		return;
	}

	stageManager->ReStart();
}

DWGameObject* DWScene::GetGameObjectByTag(const std::string& tag) const
{
	for (int i = 0; i < LayerMax; i++)
	{
		for (auto* gameObject : GameObjectList[i])
		{
			if (!gameObject)
			{
				continue;
			}

			if (gameObject->GetTag() == tag)
			{
				return gameObject;
			}
		}
	}

	return nullptr;
}

std::vector<DWGameObject*> DWScene::GetGameObjectsByTag(const std::string& tag) const
{
	std::vector<DWGameObject*> gameObjects = {};

	for (int i = 0; i < LayerMax; i++)
	{
		for (auto* gameObject : GameObjectList[i])
		{
			if (!gameObject)
			{
				continue;
			}

			if (gameObject->GetTag() == tag)
			{
				gameObjects.push_back(gameObject);
			}
		}
	}

	return gameObjects;
}
