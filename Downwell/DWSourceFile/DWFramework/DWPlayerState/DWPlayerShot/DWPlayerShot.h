//-----------------------------
//	DWPlayerShot.h[DWPlayerShotクラス制御]
//	千葉知輝
//	作成日 2025/10/15
//-----------------------------

#ifndef DWPLAYERSHOT_H
#define DWPLAYERSHOT_H

#include "DWState.h"

class DWBoxCollider;

class DWPlayerShot : public DWState
{
private:
	float		ShotCurrentFrame	= 0;
	const int	ShotIntervalFrame	= 60 / 5;
	DWBoxCollider* Collider			= nullptr;

public:
	DWPlayerShot(DWPlayer* player);

	virtual void Init()			override;
	virtual void Enter()		override;
	virtual void Update()		override;
	virtual void Exit()			override;
	virtual void NextState()	override;	// ステートの切り替えをまとめる関数
	virtual bool IsActive()	const	override;	// 移行できるかチェック
};

#endif // DWPLAYERSHOT_H