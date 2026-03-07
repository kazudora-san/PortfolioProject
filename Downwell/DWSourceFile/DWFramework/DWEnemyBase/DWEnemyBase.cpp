//-----------------------------
//	DWEnemyBase.cpp[エネミー達の継承元の処理]
//	千葉知輝
//	作成日 2025/10/24
//-----------------------------

#include "DWEnemyBase.h"

void DWEnemyBase::Uninit()
{
	DWInGameCharacter::Uninit();
}

void DWEnemyBase::Update()
{
	if (Health <= 0)
	{
		return;
	}

	DWInGameCharacter::Update();
}

void DWEnemyBase::Draw() const
{
	DWInGameCharacter::Draw();
}

void DWEnemyBase::SetEnable(bool enable)
{
	DWInGameCharacter::SetEnable(enable);
}