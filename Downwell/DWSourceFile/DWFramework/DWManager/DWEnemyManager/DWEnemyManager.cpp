//-----------------------------
//	DWEnemyManager.cpp[エネミー管理クラスの処理]
//	千葉知輝
//	作成日 2025/10/21
//-----------------------------

#include "DWEnemyManager.h"
#include "DWEnemyBase/DWEnemyBase.h"
#include "DWEnemy/DWEnemyGround/DWEnemyGround.h"

constexpr int InitEnemyMemory = 10;
#ifdef _DEBUG
#include "DWMain.h"
constexpr int EnemyView_Debug = 5;
#endif // _DEBUG


void DWEnemyManager::Init()
{
	DWScene* scene = GetScene();
	if (!scene)
	{
		return;
	}

	for(int i = 0; i < InitEnemyMemory; i++)
	{
		DWEnemyBase* enemy = scene->AddGameObject<DWEnemyGround>(EnemyLayer);

		if (!enemy)
		{
			return;
		}

		EnemyList.push_back(enemy);
	}
}

void DWEnemyManager::Uninit()
{
	EnemyList.clear();
}

void DWEnemyManager::Update()
{
#ifdef _DEBUG

	int cnt = 0;

	for (DWEnemyBase* enemy : EnemyList)
	{
		if (!enemy)
		{
			continue;
		}

		if (!enemy->GetEnable())
		{
			cnt++;
		}
	}

	printfDx("\n\n現在の敵の数%d\n\n", cnt);

	cnt = 0;
#endif // _DEBUG
}

void DWEnemyManager::SetEnemy(const DWVector2& position)
{
	for (DWEnemyBase* enemy : EnemyList)
	{
		if (!enemy)
		{
			continue;
		}

		if (!enemy->GetEnable())
		{
			enemy->SetPosition(position);
			enemy->SetEnable(true);
			enemy->SetActive(true);
			return;
		}
	}

	// InitEnemyMemory分を超えた場合、新しく追加
	DWScene* scene = GetScene();
	if (!scene)
	{
		return;
	}
	
	DWEnemyBase* enemy = scene->AddPendingGameObject<DWEnemyGround>(EnemyLayer);

	if (!enemy)
	{
		return;
	}

	enemy->SetPosition(position);
	enemy->SetEnable(true);
	enemy->SetActive(true);
	EnemyList.push_back(enemy);
}
