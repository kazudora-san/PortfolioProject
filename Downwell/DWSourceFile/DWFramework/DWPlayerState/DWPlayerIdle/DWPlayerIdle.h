//-----------------------------
//	DWPlayerIdle.h[DWPlayerIdleクラス制御]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#ifndef DWPLAYERIDLE_H
#define DWPLAYERIDLE_H

#include "DWState.h"

class DWGameObject;

class DWPlayerIdle : public DWState
{
public:
	DWPlayerIdle(DWPlayer* player);

	virtual void Init()			override;
	virtual void Enter()		override;
	virtual void Update()		override;
	virtual void Exit()			override;
	virtual void NextState()	override;	// ステートの切り替えをまとめる関数
	virtual bool IsActive()	const	override;	// 移行できるかチェック
};

#endif // DWPLAYERIDLE_H