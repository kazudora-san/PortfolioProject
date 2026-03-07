//-----------------------------
//	Camera.h[カメラ制御]
//	千葉知輝
//	作成日 2025/10/20
//-----------------------------

#ifndef DWCAMERA_H
#define DWCAMERA_H

#include "DWGameObject.h"
#include "DWPlayer/DWPlayer.h"

class DWCamera : public DWGameObject
{
private:
	DWVector2*	OriginalPosition	= {}; // カメラのポジションを元に戻す用
	DWPlayer*	PlayerPosition		= nullptr;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;
	virtual void	Reset() override;
};

#endif // CAMERA_H
