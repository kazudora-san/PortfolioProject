//-----------------------------
//	DWPlayerIdle.cpp[プレイヤーが何もしていない時の処理]
//	千葉知輝
//	作成日 2025/10/02
//-----------------------------

#include "DWPlayerIdle.h"
#include "DWComponent/DWStateMachine/DWStateMachine.h"


DWPlayerIdle::DWPlayerIdle(DWPlayer* player)
{
	StateName = "PlayerIdle";
	Player = player;
}

void DWPlayerIdle::Init()
{
	if (!StateMachine)
	{
		return;
	}

	// 追加したいStateを名前検索して、入れる
	if(DWState* moveState = StateMachine->FindState("PlayerMove"))
	{
		RelevantStates.push_back(moveState);
	}
	if (DWState* jumpState = StateMachine->FindState("PlayerJump"))
	{
		RelevantStates.push_back(jumpState);
	}
}

void DWPlayerIdle::Enter()
{
	Player->SetVelocity({});
}

void DWPlayerIdle::Update()
{
	// nullチェック
	if (!Player)
	{
		return;
	}
	
	NextState();
}

void DWPlayerIdle::Exit()
{
}

void DWPlayerIdle::NextState()
{
	// 切り替える可能性のあるStateクラスのIsActive()を呼ぶ必要がある
	for (auto* state : RelevantStates)
	{
		if (!state)
		{
			continue;
		}

		if (state->IsActive())
		{
			DWStateMachine* stateMachine = state->GetStateMachine();

			if (!stateMachine)
			{
				continue;
			}

			stateMachine->ChangeState(state->GetStateName());
		}
	}
}

bool DWPlayerIdle::IsActive() const
{
	// このステートクラスに移行するかの条件
	// nullチェック
	if (!Player)
	{
		return false;
	}

	const DWInput* input = GetInput();

	if (!input)
	{
		return false;
	}

	return (Player->GetHealth() > 0.0f &&
			!(input->GetLeftMove() || input->GetRightMove()));
}
