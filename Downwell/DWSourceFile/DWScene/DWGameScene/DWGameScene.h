//-----------------------------
//	DWGameScene.h[DWGameSceneクラス制御]
//	千葉知輝
//	作成日 2025/10/14
//-----------------------------

#ifndef DWGAMESCENE_H
#define DWGAMESCENE_H

#include "DWScene/DWScene.h"
#include "DWGoal/DWGoal.h"

class DWGameScene : public DWScene
{
private:
	DWGoal* GoalFlag = nullptr;

public:
	DWGameScene(DWSceneManager* sceneManager, const std::string& sceneName);	// 必ずシーンの名前を入れること

	virtual void	Init()		override;
	virtual void	Update()	override;
};

#endif // DWGAMESCENE_H