//-----------------------------
//	DWGameScene.cpp[シーン処理]
//	千葉知輝
//	作成日 2025/10/14
//-----------------------------
#include "DWGameScene.h"
#include "DWManager/DWColliderManager/DWColliderManager.h"
#include "DWManager/DWEnemyManager/DWEnemyManager.h"
#include "DWManager/DWBulletManager/DWBulletManager.h"
#include "DWManager/DWBlockManager/DWBlockManager.h"
#include "DWManager/DWStageManager/DWStageManager.h"
#include "DWManager/DWAudioManager/DWAudioManager.h"
#include "DWPlayer/DWPlayer.h"
#include "DWCamera/DWCamera.h"
#include "DWUI/DWPlayerUI/DWPlayerHealthUI/DWPlayerHealthUI.h"
#include "DWUI/DWPlayerUI/DWAmmoUI/DWAmmoUI.h"
#include "DWUI/DWWSystemUI/DWResultUI/DWResultUI.h"

DWGameScene::DWGameScene(DWSceneManager* sceneManager, const std::string& sceneName)
{
	SceneManager = sceneManager;
	SceneName = sceneName;
}

void DWGameScene::Init()
{
	AddManager<DWColliderManager>();
	AddManager<DWEnemyManager>();
	AddManager<DWBulletManager>();
	AddManager<DWBlockManager>();
	AddManager<DWStageManager>();
	AddManager<DWAudioManager>();
	AddGameObject<DWPlayer>(PlayerLayer);
	AddGameObject<DWCamera>(BackLayer);
	GoalFlag = AddGameObject<DWGoal>(BackLayer);
	AddGameObject<DWPlayerHealthUI>(UILayer);
	AddGameObject<DWAmmoUI>(UILayer);
	AddGameObject<DWCurrentStageUI>(UILayer);
	AddGameObject<DWResultUI>(UILayer);
}

void DWGameScene::Update()
{
	if (!GoalFlag)
	{
		return;
	}

	if (GoalFlag->GetGoalFlag() || bRestartFlag)
	{
		for (int i = 0; i < LayerMax; i++)
		{
			for (DWGameObject* gameObject : GameObjectList[i])
			{
				if (!gameObject)
				{
					continue;
				}

				gameObject->Reset();
			}
		}

		for (DWManager* manager : ManagerList)
		{
			if (!manager)
			{
				continue;
			}

			manager->Reset();
		}

		bRestartFlag = false;
	}
	else
	{
		DWScene::Update();
	}
	
}