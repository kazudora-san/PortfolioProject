//-----------------------------
//	DWBlockManager.cpp[ブロック管理クラスの処理]
//	千葉知輝
//	作成日 2025/10/23
//-----------------------------

#include "DWBlockManager.h"
#include "DWBlock/DWNormalBlock/DWNormalBlock.h"
#include "DWBlock/DWBreakBlock/DWBreakBlock.h"

constexpr int InitNormalBlockMemory = 10;
constexpr int InitBreakBlockMemory = 5;

void DWBlockManager::Init()
{
	DWScene* scene = GetScene();
	if (!scene)
	{
		return;
	}

	for (int i = 0; i < InitNormalBlockMemory; i++)
	{
		DWNormalBlock* normalBlock = scene->AddGameObject<DWNormalBlock>(BlockLayer);

		if (!normalBlock)
		{
			return;
		};

		normalBlock->SetEnable(false);

		BlockList.push_back(normalBlock);
	}
}

void DWBlockManager::Uninit()
{
	BlockList.clear();
}

void DWBlockManager::Update()
{
}

void DWBlockManager::SetBlock(const DWVector2& position, BlockType type)
{
	for (DWBlockBase* block : BlockList)
	{
		if (!block)
		{
			continue;
		}

		if (!block->GetEnable())
		{
			block->SetPosition(position);
			block->SetActive(true);
			block->SetEnable(true);
			return;
		}
	}

	// InitでInitBlockMemory分メモリを確保しているが
	// それ以上のBlockを生成する場合、AddGameObjectを呼ぶ
	DWScene* scene = GetScene();

	if (!scene)
	{
		return;
	}

	switch (type)
	{
		case NormalBlock:
		{
			DWNormalBlock* normalBlock = scene->AddPendingGameObject<DWNormalBlock>(BlockLayer);
			if (!normalBlock)
			{
				return;
			}

			normalBlock->SetPosition(position);
			normalBlock->SetActive(true);
			normalBlock->SetEnable(true);
			BlockList.push_back(normalBlock);

			break;
		}
		case BreakBlock:
		{
			DWBreakBlock* breakBlock = scene->AddPendingGameObject<DWBreakBlock>(BlockLayer);

			breakBlock->SetPosition(position);
			breakBlock->SetActive(true);
			breakBlock->SetEnable(true);
			BlockList.push_back(breakBlock);

			break;
		}
		default:
		{
			break;
		}
	}
}