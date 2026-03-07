//-----------------------------
//	DWStaticMachine.cpp[DWStaticMachine処理]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#include "DWStateMachine.h"
#include "DxLib.h"

DWStateMachine::DWStateMachine(DWGameObject* owner)
{
	OwnerObject = owner;
}

void DWStateMachine::Init()
{
	for (auto* state : StateList)
	{
		// nullチェック
		if (!state)
		{
			continue;
		}

		state->Init();
	}
}

void DWStateMachine::Uninit()
{
	// メモリの開放
	for (auto state : StateList)
	{
		if (!state)
		{
			continue;
		}

		delete state;
		state = nullptr;
	}

	// 初期化
	StateList.clear();

	DWComponent::Uninit();
}

void DWStateMachine::Update()
{
	// nullチェック
	if (!CurrentState)
	{
		return;
	}
	
	CurrentState->Update();
}

void DWStateMachine::RegistState(DWState* state)
{
	// nullチェック
	if (!state)
	{
		return;
	}

	StateList.push_back(state);
	state->SetStateOwner(OwnerObject);
	state->SetStateMachine(this);
}

void DWStateMachine::ChangeState(const std::string& stateName)
{
	// リスト格納分回す
	for (DWState* state : StateList)
	{
		// nullチェック
		if (!state)
		{
			continue;
		}

		// ステートクラスのStateNameと引数の名前を比較する
		if (state->GetStateName() == stateName)
		{
			// nullチェック
			if (CurrentState)
			{
				// 最低限の初期化をする
				CurrentState->Exit();
			}

			// 現在のステートに格納する
			CurrentState = state;
			
			// nullチェック
			if (CurrentState)
			{
				// 最低限の初期化をする
				CurrentState->Enter();
			}

			// 見つかったらfor分を抜ける
			break;
		}
	}
}

DWState* DWStateMachine::FindState(const std::string& stateName) const
{
	for (DWState* state : StateList)
	{
		if (!state)
		{
			continue;
		}

		if (state->GetStateName() == stateName)
		{
			return state;
		}
	}

	return nullptr;
}
