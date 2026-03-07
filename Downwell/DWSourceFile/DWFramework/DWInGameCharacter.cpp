//-----------------------------
//	DWInGameCharavter.cpp[ゲームキャラクターの制御]
//	千葉知輝
//	作成日 2025/10/02
//-----------------------------

#include "DWInGameCharacter.h"

void DWInGameCharacter::Uninit()
{
	DWGameObject::Uninit();
}

void DWInGameCharacter::Update()
{
	DWGameObject::Update();
}

void DWInGameCharacter::Draw() const
{
	DWGameObject::Draw();
}

void DWInGameCharacter::SetEnable(bool enable)
{
	DWGameObject::SetEnable(enable);
}

void DWInGameCharacter::TakeDamage(const float damage)
{
	Health -= damage;
}