//-----------------------------
//	DWState.h[DWStateクラス制御]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#ifndef DWSTATE_H
#define DWSTATE_H

#include <string>
#include <vector>
#include "DWGameObject.h"
#include "DWPlayer/DWPlayer.h"
#include "DWInput/DWInput.h"

class DWStateMachine;

class DWState
{
protected:
	std::string		StateName				= {};				// ステートの名前
	DWGameObject*	StateOwner				= nullptr;			// ステートを利用するオブジェクト
	std::vector<DWState*> RelevantStates	= {};
	DWStateMachine* StateMachine			= nullptr;
	DWPlayer*		Player					= nullptr;

public:
	virtual void	Init()		= 0;					// 初期化処理
	virtual void	Enter()		= 0;					// "切り替わったとき"に呼ばれる、最低限の初期化処理(テクスチャ読み込みなど不要なものは×)
	virtual void	Update()	= 0;
	virtual void	Exit()		= 0;					// 現在のステートの最低限の終了処理
	virtual void	NextState()	= 0;					// ステートの切り替えをまとめる関数
	virtual bool	IsActive()	const { return false; }	// このステートが実行できるかチェック

	void				SetStateOwner	(DWGameObject* owner)	{ StateOwner = owner; }
	const std::string&	GetStateName	()	const				{ return StateName; }
	DWGameObject*		GetStateOwner	()	const				{ return StateOwner; }
	void				SetStateMachine	(DWStateMachine* machine)	{ StateMachine = machine; }
	DWStateMachine*		GetStateMachine	()	const					{ return StateMachine; }
	DWInput*			GetInput		()	const;
	
};

#endif // DWSTATE_H