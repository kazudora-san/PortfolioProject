//-----------------------------
//	DWStateMachine.h[DWStateMachineクラス制御]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#ifndef DWSTATEMACHINE_H
#define DWSTATEMACHINE_H

#include <list>
#include "DWComponent/DWComponent.h"
#include "DWState.h"

class DWState;

class DWStateMachine : public DWComponent
{
private:
	std::list<DWState*>	StateList		= {};	// ステートクラスを格納しておく
	DWState*			CurrentState	= nullptr;

public:
	DWStateMachine() = default;
	DWStateMachine(DWGameObject* owner);
	
	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;

	void		RegistState		(DWState* state);
	DWState*	GetCurrentState	()	const					{ return CurrentState; }		// 相手の現在のステートをもってくる
	void		ChangeState		(const std::string&	stateName);								// 名前で比較する(詳細はcppを参照)
	DWState*	FindState		(const std::string& stateName)	const;						// 名前で比較して、ステートを探す
};

#endif // DWSTATEMACHINE_H