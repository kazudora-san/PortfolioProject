//-----------------------------
//	DWPlayerJump.h[DWPlayerJumpクラス制御]
//	千葉知輝
//	作成日 2025/10/15
//-----------------------------

#ifndef DWPLAYERJUMP_H
#define DWPLAYERJUMP_H

#include "DWState.h"

class DWGameObject;

constexpr int MaxJumpFrame = 20;

class DWPlayerJump : public DWState
{
private:
	const int	MaxHoldFrame		= MaxJumpFrame;
	int			CurrentHoldFrame	= 0;

public:
	DWPlayerJump(DWPlayer* player);

	virtual void Init()			override;
	virtual void Enter()		override;
	virtual void Update()		override;
	virtual void Exit()			override;
	virtual void NextState()	override;	// ステートの切り替えをまとめる関数
	virtual bool IsActive()	const	override;	// 移行できるかチェック
};

#endif // DWPLAYERJUMP_H