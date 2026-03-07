//-----------------------------
//	DWSection.cpp[ステージの１区画作成の処理]
//	千葉知輝
//	作成日 2025/10/22
//-----------------------------

#include "DWSection.h"
#include <vector>

// 配列の一番目＝スタート区画と、最後＝ゴール区画にする
int Field[SectionHeight][SectionWidth][MaxSection] =
{
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	},
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 1},
		{1, 0, 0, 0, 0, 3, 2, 0, 0, 1},
		{1, 0, 0, 0, 0, 2, 1, 0, 0, 1},
		{1, 0, 0, 3, 2, 1, 1, 0, 0, 1},
		{1, 0, 0, 2, 1, 1, 1, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	},
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 2, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 3, 3, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	},
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{1, 3, 0, 0, 0, 0, 0, 0, 3, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	},
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 0, 1, 1, 0, 0, 3, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 3, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 1, 1},
		{1, 3, 1, 1, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 3, 3, 0, 1},
		{1, 0, 0, 0, 1, 1, 3, 3, 0, 1},
		{1, 1, 3, 1, 1, 1, 2, 2, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	},
	{
		{1, 0, 0, 0, 1, 1, 0, 0, 3, 1},
		{1, 3, 3, 3, 1, 1, 2, 2, 2, 1},
		{1, 2, 2, 2, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 3, 0, 0, 1},
		{1, 3, 3, 3, 1, 1, 2, 2, 2, 1},
		{1, 2, 2, 2, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 1, 0, 3, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 1},
	},
	{
		{1, 0, 0, 0, 0, 0, 0, 3, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 3, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	},
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 3, 0, 0, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 3, 0, 0, 1, 1},
		{1, 1, 1, 2, 2, 2, 2, 1, 1, 1},
		{1, 1, 1, 1, 2, 2, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	},
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 2, 2, 1, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	},
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	},
};

void DWSection::Init()
{
}

void DWSection::Uninit()
{
	DWGameObject::Uninit();
}

void DWSection::Update()
{
}

void DWSection::Draw() const
{
}

void DWSection::Reset()
{
}

void DWSection::CreateSection(int index, const DWVector2& offset)
{
	if (!Scene)
	{
		return;
	}

	if (index < 0 || MaxSection <= index)
	{
		return;
	}

	EnemyManager = Scene->GetManager<DWEnemyManager>();
	if (!EnemyManager)
	{
		return;
	}

	BlockManager = Scene->GetManager<DWBlockManager>();
	if (!BlockManager)
	{
		return;
	}

	// フィールドデータ読み込み
	for (int i = 0; i < SectionHeight; i++)
	{
		for (int j = 0; j < SectionWidth; j++)
		{
			Section[i][j] = Field[index][i][j];
		}
	}

	// フィールドに設置
	for (int i = 0; i < SectionHeight; i++)
	{
		for (int j = 0; j < SectionWidth; j++)
		{
			// ｉ：縦
			// ｊ：横
			switch (Section[i][j])
			{
			case None:
			{
				break;
			}
			case BlockNormal:
			{
				BlockManager->SetBlock({ FieldOffset.x + TileSize.x * j + offset.x,
											FieldOffset.y + TileSize.y * i + offset.y }, NormalBlock);

				break;
			}
			case BlockBreak:
			{
				BlockManager->SetBlock({ FieldOffset.x + TileSize.x * j + offset.x,
											FieldOffset.y + TileSize.y * i + offset.y }, BreakBlock);
				break;
			}
			case EnemyGround:
			{
				EnemyManager->SetEnemy({ FieldOffset.x + TileSize.x * j + offset.x,
											FieldOffset.y + TileSize.y * i + offset.y });

				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}

void DWSection::ResetSection(int index, const DWVector2& offset)
{
	if (!Scene)
	{
		return;
	}

	if (index < 0 || MaxSection <= index)
	{
		return;
	}

	if (!EnemyManager)
	{
		EnemyManager = Scene->GetManager<DWEnemyManager>();

		if (!EnemyManager)
		{
			return;
		}
	}

	if (!BlockManager)
	{
		BlockManager = Scene->GetManager<DWBlockManager>();

		if (!BlockManager)
		{
			return;
		}
	}

	// フィールドデータ読み込み
	for (int i = 0; i < SectionHeight; i++)
	{
		for (int j = 0; j < SectionWidth; j++)
		{
			Section[i][j] = Field[index][i][j];
		}
	}

	// フィールドに設置
	for (int i = 0; i < SectionHeight; i++)
	{
		for (int j = 0; j < SectionWidth; j++)
		{
			// ｉ：縦
			// ｊ：横
			switch (Section[i][j])
			{
			case None:

				break;

			case BlockNormal:
				BlockManager->SetBlock({ FieldOffset.x + TileSize.x * j + offset.x,
											FieldOffset.y + TileSize.y * i + offset.y }, NormalBlock);

				break;

			case EnemyGround:
				EnemyManager->SetEnemy({ FieldOffset.x + TileSize.x * j + offset.x,
											FieldOffset.y + TileSize.y * i + offset.y });

				break;

			default:
				break;
			}
		}
	}
}
