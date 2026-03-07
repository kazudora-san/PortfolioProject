//-----------------------------
//	DWManager.h[DWManagerクラス制御]
//	千葉知輝
//	作成日 2025/10/17
//-----------------------------

#ifndef DWMANAGER_H
#define DWMANAGER_H

#include "DWScene/DWScene.h"

class DWManager
{
private:
	DWScene*	Scene	= nullptr;

public:
	virtual void	Init()		= 0;
	virtual void	Uninit()	= 0;
	virtual void	Update()	= 0;

	virtual void	Reset() {};

	void SetScene(DWScene* scene) { Scene = scene; }
	DWScene*	GetScene()	const { return Scene; }
};

#endif // DWMANAGER_H