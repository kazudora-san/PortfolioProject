//-----------------------------
//	DWStageManager.cpp[ステージ生成管理の処理]
//	千葉知輝
//	作成日 2025/10/24
//-----------------------------

#include "DWStageManager.h"
#include "DWMain.h"

void DWStageManager::Init()
{
	DWScene* scene = GetScene();
	if (!scene)
	{
		return;
	}

	// Sectionの０番目とMaxSection - 1はスタートとゴールのため最初と最後にいれる
	std::vector<int> numbers = {};

	// vector型なので、最初にゴール、一番最後にスタートをpush_backする
	numbers.push_back(MaxSection - 1);

	for (int i = 0; i < MiddleSection; i++)
	{
		// 欲しい値が”重複無し”1～8
		int random = 0;
		bool duplicate = false;

		do
		{
			random = GetRand(MaxSection - 3) + 1;
			duplicate = false;

			// 数字がダブっている間は再度乱数を取得
			for (int num : numbers)
			{
				if (num == random)
				{
					duplicate = true;
					break;
				}
			}

		} while (duplicate);

		// ランダムに格納した数字をSpwanSectionで使用する
		numbers.push_back(random);
	}

	numbers.push_back(0);

	for(int i = 0; i < StageSection; i++)
	{
		DWSection* section = scene->AddGameObject<DWSection>(BlockLayer);
		if (!section)
		{
			return;
		}

		SectionList.push_back(section);

		if (numbers.empty())
		{
			return;
		}

		int number = numbers.back();
		numbers.pop_back();

		SpwanSection(i, number, { 0.0f, i * 1000.0f });
	}
}

void DWStageManager::Uninit()
{
	SectionList.clear();
}

void DWStageManager::Update()
{
}

void DWStageManager::CurrentStageView()
{
	if (!CurrentStageUI)
	{
		return;
	}

	if (!bStageViewFlag)
	{
		return;
	}

	bStageViewFlag = false;
	CurrentStageUI->CurrentStageDispFlag(CurrentStageNumber);
}

void DWStageManager::SetStageUI(DWCurrentStageUI* stageUI)
{
	if (!stageUI)
	{
		return;
	}

	CurrentStageUI = stageUI;
}

void DWStageManager::Reset()
{
	bStageViewFlag = true;

	// Sectionの０番目とMaxSection - 1はスタートとゴールのため最初と最後にいれる
	std::vector<int> numbers = {};

	// vector型なので、最初にゴール、一番最後にスタートをpush_backする
	numbers.push_back(MaxSection - 1);

	for (int i = 0; i < MiddleSection; i++)
	{
		// 欲しい値が”重複無し”1～8
		int random = 0;
		bool duplicate = false;

		do
		{
			random = GetRand(MaxSection - 3) + 1;
			duplicate = false;

			// 数字がダブっている間は再度乱数を取得
			for (int num : numbers)
			{
				if (num == random)
				{
					duplicate = true;
					break;
				}
			}

		} while (duplicate);

		// ランダムに格納した数字をSpwanSectionで使用する
		numbers.push_back(random);
	}

	numbers.push_back(0);
	int count = 0;

	for (DWSection* section : SectionList)
	{
		if (!section)
		{
			return;
		}

		int number = numbers.back();
		numbers.pop_back();

		section->ResetSection(number, { 0.0f, count * 1000.0f });
		
		count++;
	}

	if (bRestartFlag)
	{
 		CurrentStageNumber = 1;
		bRestartFlag = false;
	}
	else
	{
		CurrentStageNumber++;
	}
}

void DWStageManager::CreateStage()
{
}

void DWStageManager::SpwanSection(int currentIndex, int sectionIndex, const DWVector2& offset)
{
	if (!SectionList[currentIndex])
	{
		return;
	}

	// sectionIndex = MaxSection - 1の範囲で呼ぶ
	// offset = 生成する回数によって、開始する位置の調整をする
	SectionList[currentIndex]->CreateSection(sectionIndex, offset);
}