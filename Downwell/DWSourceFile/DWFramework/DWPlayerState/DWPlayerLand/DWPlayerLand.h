//-----------------------------
//	DWPlayerLand.h[DWPlayerLandクラス制御]
//	千葉知輝
//	作成日 2025/10/15
//-----------------------------

#ifndef DWPLAYERLAND_H
#define DWPLAYERLAND_H

#include "DWState.h"

class DWGameObject;
class DWBoxCollider;

class DWPlayerLand : public DWState
{
private:
	DWBoxCollider*	Collider	= nullptr;

public:
	DWPlayerLand(DWPlayer* player);

	virtual void Init()				override;
	virtual void Enter()			override;
	virtual void Update()			override;
	virtual void Exit()				override;
	virtual void NextState()		override;	// ステートの切り替えをまとめる関数
	virtual bool IsActive() const	override;
};

#endif // DWPLAYERLAND_H