//-----------------------------
//	DWBlockBase.cpp[ブロック達の継承元の処理]
//	千葉知輝
//	作成日 2025/10/30
//-----------------------------

#include "DWBlockBase.h"

void DWBlockBase::Uninit()
{
	DWGameObject::Uninit();
}

void DWBlockBase::Update()
{
	DWGameObject::Update();
}

void DWBlockBase::Draw() const
{
	DWGameObject::Draw();
}

void DWBlockBase::SetEnable(bool enable)
{
	DWGameObject::SetEnable(enable);
}