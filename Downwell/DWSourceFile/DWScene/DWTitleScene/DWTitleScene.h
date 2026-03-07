//-----------------------------
//	DWTitleScene.h[DWTitleSceneクラス制御]
//	千葉知輝
//	作成日 2025/10/31
//-----------------------------

#ifndef DWTITLESCENE_H
#define DWTITLESCENE_H

#include "DWScene/DWScene.h"

class DWTitleScene : public DWScene
{
public:
	DWTitleScene(DWSceneManager* sceneManager, const std::string& sceneName);	// 必ずシーンの名前を入れること

	virtual void	Init()		override;
	virtual void	Update()	override;
};

#endif // DWTITLESCENE_H