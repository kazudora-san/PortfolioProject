//-----------------------------
//	DWPlayerUI.cpp[PlayerUIˆ—]
//	ç—t’m‹P
//	ì¬“ú 2025/10/29
//-----------------------------

#include "DWPlayerUI.h"

void DWPlayerUI::Init()
{
	DWUI::Init();

	if (!Scene)
	{
		return;
	}

	OwnerObject = Scene->GetGameObject<DWPlayer>();

	Tag = "PlayerUI";
}

void DWPlayerUI::Uninit()
{
	DWUI::Uninit();

	if (OwnerObject)
	{
		OwnerObject = nullptr;
	}
}

void DWPlayerUI::Update()
{
	DWUI::Update();
}
