//-----------------------------
//	DWPlayerJump.cpp[プレイヤーがジャンプ中の処理]
//	千葉知輝
//	作成日 2025/10/15
//-----------------------------
#include "DWPlayerJump.h"
#include "DWComponent/DWStateMachine/DWStateMachine.h"


DWPlayerJump::DWPlayerJump(DWPlayer* player)
{
	StateName = "PlayerJump";
	Player = player;
}

void DWPlayerJump::Init()
{
	if (!StateMachine)
	{
		return;
	}

	// 追加したいStateを名前検索して、入れる
	if (DWState* fallState = StateMachine->FindState("PlayerFall"))
	{
		RelevantStates.push_back(fallState);
	}
	if (DWState* landState = StateMachine->FindState("PlayerLand"))
	{
		RelevantStates.push_back(landState);
	}
}

void DWPlayerJump::Enter()
{
	if (!Player)
	{
		return;
	}

	CurrentHoldFrame = 0;
	Player->Jump(static_cast<float>(CurrentHoldFrame));
}

void DWPlayerJump::Update()
{
	CurrentHoldFrame++;

	if (Player)
	{
		Player->Move();

		if (MaxHoldFrame >= CurrentHoldFrame)
		{
			const DWInput* input = GetInput();

			if (input)
			{
				if (Player->GetHealth() > 0.0f && input->GetActionKey())
				{
					float t = static_cast<float>(CurrentHoldFrame / MaxHoldFrame);
					Player->Jump(Player->GetExtraUpAccel() * 1 - t);
					
					return;
				}

			}
		}
	}

	NextState();
}

void DWPlayerJump::Exit()
{
}

void DWPlayerJump::NextState()
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

bool DWPlayerJump::IsActive() const
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
			input->GetActionDown());
}
