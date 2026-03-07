//-----------------------------
//	DWTitleScene.cpp[タイトルシーン処理]
//	千葉知輝
//	作成日 2025/10/31
//-----------------------------
#include "DWTitleScene.h"
#include "DWTitle/DWTitleLogo/DWTitleLogo.h"
#include "DWTitle/DWTitleButton/DWTitleButton.h"
#include "DWManager/DWAudioManager/DWAudioManager.h"

DWTitleScene::DWTitleScene(DWSceneManager* sceneManager, const std::string& sceneName)
{
	SceneManager = sceneManager;
	SceneName = sceneName;
}

void DWTitleScene::Init()
{
	AddManager<DWAudioManager>();
	AddGameObject<DWTitleLogo>(BackLayer);
	AddGameObject<DWTitleButton>(BackLayer);
}

void DWTitleScene::Update()
{
	DWScene::Update();
}