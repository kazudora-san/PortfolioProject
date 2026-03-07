//-----------------------------
//	DWBulletManager.cpp[弾管理クラスの処理]
//	千葉知輝
//	作成日 2025/10/17
//-----------------------------

#include "DWBulletManager.h"
#include "DWScene/DWScene.h"
#include "DWPlayer/DWPlayer.h"

void DWBulletManager::Init()
{
	DWScene* scene = GetScene();
	if (!scene)
	{
		return;
	}

	const int memoryMaxAmmo = MaxAmmoCount;

	for (int i = 0; i < memoryMaxAmmo; i++)
	{
		DWBullet* bullet = scene->AddGameObject<DWBullet>(BulletLayer);

		if (!bullet)
		{
			return;
		}

		BulletList.push_back(bullet);
	}
}

void DWBulletManager::Uninit()
{
	BulletList.clear();
}

void DWBulletManager::Update()
{
#ifdef _DEBUG

	int cnt = 0;

	for (DWBullet* bullet : BulletList)
	{
		if (!bullet)
		{
			continue;
		}

		if (bullet->GetEnable())
		{
			cnt++;
		}
	}

	printfDx("現在の弾の数%d\n", cnt);

	cnt = 0;
#endif // _DEBUG
}

void DWBulletManager::SetBullet(const DWVector2& position)
{
	for (DWBullet* bullet : BulletList)
	{
		if (!bullet)
		{
			continue;
		}

		if (!bullet->GetEnable())
		{
			bullet->SetPosition(position);
			bullet->SetEnable(true);
			bullet->SetActive(true);
			return;
		}
	}

	// InitでPlayer->MaxAmmo()分メモリを確保しているが
	// それ以上の弾を打つ場合、AddGameObjectを呼ぶ
	DWScene* scene = GetScene();
	
	if (!scene)
	{
		return;
	}
	
	DWBullet* bullet = scene->AddPendingGameObject<DWBullet>(BulletLayer);

	if (!bullet)
	{
		return;
	}

	bullet->SetPosition(position);
	bullet->SetEnable(true);
	bullet->SetActive(true);
	BulletList.push_back(bullet);
}
