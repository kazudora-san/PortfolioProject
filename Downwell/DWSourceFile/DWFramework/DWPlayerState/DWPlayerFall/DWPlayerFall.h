//-----------------------------
//	DWPlayerFall.h[DWPlayerFallクラス制御]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#ifndef DWPLAYERFALL_H
#define DWPLAYERFALL_H

#include "DWState.h"

class DWBoxCollider;

class DWPlayerFall : public DWState
{
private:
	DWBoxCollider* Collider = nullptr;

public:
	DWPlayerFall(DWPlayer* player);

	virtual void Init()			override;
	virtual void Enter()		override;
	virtual void Update()		override;
	virtual void Exit()			override;
	virtual void NextState()	override;	// ステートの切り替えをまとめる関数
	virtual bool IsActive()	const	override;	// 移行できるかチェック
};

#endif // DWPLAYERFALL_H