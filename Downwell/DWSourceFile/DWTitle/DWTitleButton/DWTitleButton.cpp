//-----------------------------
//	DWTitleButton.cpp[タイトルpushボタン処理]
//	千葉知輝
//	作成日 2025/10/31
//-----------------------------

#include "DWMain.h"
#include "DWTitleButton.h"
#include "DWInput/DWInput.h"
#include "DWScene/DWScene.h"
#include "DWScene/DWSceneManager.h"
#include "DWScene/DWGameScene/DWGameScene.h"
#include "DWManager/DWAudioManager/DWAudioManager.h"

void DWTitleButton::Init()
{
	Input = GetInput();
}

void DWTitleButton::Uninit()
{
	DWGameObject::Uninit();
}

void DWTitleButton::Update()
{
	DWGameObject::Update();

	if (!Input)
	{
		return;
	}

	if (bPushActionKey)
	{
		CurrentFrame++;

		if (CurrentFrame < WaitFrame)
		{
			return;
		}

		if (!Scene)
		{
			return;
		}

		DWSceneManager* sceneManager = Scene->GetSceneManager();
		if (!sceneManager)
		{
			return;
		}

		sceneManager->ChangeScene(new DWGameScene(sceneManager, "Game"));
	}

	if (Input->GetActionDown())
	{
		DWAudioManager* audioManager = Scene->GetManager<DWAudioManager>();
		if (audioManager)
		{
			audioManager->PlaySE("Start");
		}

		bPushActionKey = true;
	}
}

void DWTitleButton::Draw() const
{
	DWGameObject::Draw();
}

void DWTitleButton::Reset()
{
	bPushActionKey = false;
	CurrentFrame = 0;
}

void DWTitleButton::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
}