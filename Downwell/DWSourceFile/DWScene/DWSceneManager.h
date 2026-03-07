//-----------------------------
//	DWSceneManager.h[DWSceneManagerクラス制御]
//	千葉知輝
//	作成日 2025/10/14
//-----------------------------

#ifndef DWSCENEMANAGER_H
#define DWSCENEMANAGER_H

#include "DWScene.h"

class DWSceneManager
{
private:
	DWScene*				Scene		= nullptr;
	DWScene*				NextScene	= nullptr;
	DWInput*				Input		= nullptr;

private:
	void ChangeSceneProcess();

public:
	DWSceneManager();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ChangeScene(DWScene* nextScene);
	DWInput* GetInput()	const { return Input; }
};

#endif // DWSCENEMANAGER_H