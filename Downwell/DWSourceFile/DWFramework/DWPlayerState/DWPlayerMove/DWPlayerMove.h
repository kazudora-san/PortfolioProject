//-----------------------------
//	DWPlayerMove.h[DWPlayerMoveクラス制御]
//	千葉知輝
//	作成日 2025/10/09
//-----------------------------

#ifndef DWPlayerMove_H
#define DWPlayerMove_H

#include "DWState.h"

class DWPlayerMove : public DWState
{
public:
	DWPlayerMove(DWPlayer* player);

	virtual void Init()				override;
	virtual void Enter()			override;
	virtual void Update()			override;
	virtual void Exit()				override;
	virtual void NextState()		override;
	virtual bool IsActive() const	override;
};

#endif // DWPlayerMove_H