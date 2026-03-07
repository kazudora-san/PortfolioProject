//-----------------------------
//	DWSceneManager.cpp[シーン処理]
//	千葉知輝
//	作成日 2025/10/14
//-----------------------------
#include "DWSceneManager.h"
#include "DWTitleScene/DWTitleScene.h"
#include "DWInput/DWInput.h"

DWSceneManager::DWSceneManager()
{
}

void DWSceneManager::Init()
{
	Scene = new DWTitleScene(this, "Title");
	Input = new DWInput();

	if (!Scene)
	{
		return;
	}

	Scene->Init();
}

void DWSceneManager::Uninit()
{
	if (Input)
	{
		delete Input;
		Input = nullptr;
	}

	if (Scene)
	{
		Scene->Uninit();
		delete Scene;
		Scene = nullptr;
	}
}

void DWSceneManager::Update()
{
	if (Scene)
	{
		Scene->Update();
	}
	
	if (Input)
	{
		Input->UpdateKey();
	}
	
	ChangeSceneProcess();
}

void DWSceneManager::Draw()
{
	if (!Scene)
	{
		return;
	}

	Scene->Draw();
}

void DWSceneManager::ChangeSceneProcess()
{
	if (!NextScene)
	{
		return;
	}

	if (Scene == NextScene)
	{
		NextScene = nullptr;
		return;
	}

	if (Scene)
	{
		Scene->Uninit();
		delete Scene;
	}

	Scene = NextScene;
	Scene->Init();

	NextScene = nullptr;
}

void DWSceneManager::ChangeScene(DWScene* nextScene)
{
	NextScene = nextScene;
}

