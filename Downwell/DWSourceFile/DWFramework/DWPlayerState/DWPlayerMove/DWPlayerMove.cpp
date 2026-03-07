//-----------------------------
//	DWPlayerMove.cpp[プレイヤーが何もしていない時の処理]
//	千葉知輝
//	作成日 2025/10/09
//-----------------------------

#include "DWPlayerMove.h"
#include "DWComponent/DWStateMachine/DWStateMachine.h"

DWPlayerMove::DWPlayerMove(DWPlayer* player)
{
	StateName = "PlayerMove";
	Player = player;
}

void DWPlayerMove::Init()
{
	if (!StateMachine)
	{
		return;
	}

	// 追加したいStateを名前検索して、入れる
	if (DWState* idleState = StateMachine->FindState("PlayerIdle"))
	{
		RelevantStates.push_back(idleState);
	}
	if (DWState* fallState = StateMachine->FindState("PlayerFall"))
	{
		RelevantStates.push_back(fallState);
	}
	if (DWState* jumpState = StateMachine->FindState("PlayerJump"))
	{
		RelevantStates.push_back(jumpState);
	}
}

void DWPlayerMove::Enter()
{
}

void DWPlayerMove::Update()
{
	if (!Player)
	{
		return;
	}

	Player->Move();

	NextState();
}

void DWPlayerMove::Exit()
{
}

void DWPlayerMove::NextState()
{
	// 切り替える可能性のあるStateクラスのIsActive()を呼ぶ必要がある
	for (auto* state : RelevantStates)
	{
		if (!state)
		{
			continue;
		}

		DWStateMachine* stateMachine = state->GetStateMachine();

		if (!stateMachine)
		{
			continue;
		}

		if (state->IsActive())
		{
			stateMachine->ChangeState(state->GetStateName());
		}
	}
}

bool DWPlayerMove::IsActive() const
{
	// このステートクラスに移行するかの条件
	if (!Player)
	{
		return false;
	}

	const DWInput* input = GetInput();

	if (!input)
	{
		return false;
	}

	return(Player->GetHealth() > 0.0f &&
			input->GetLeftMove() || input->GetRightMove());
}
