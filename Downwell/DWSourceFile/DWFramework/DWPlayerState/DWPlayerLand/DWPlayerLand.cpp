//-----------------------------
//	DWPlayerLand.cpp[プレイヤーが地面についた時の処理]
//	千葉知輝
//	作成日 2025/10/15
//-----------------------------

#include "DWPlayerLand.h"
#include "DWComponent/DWStateMachine/DWStateMachine.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"


DWPlayerLand::DWPlayerLand(DWPlayer* player)
{
	StateName = "PlayerLand";
	Player = player;
}

void DWPlayerLand::Init()
{
	if (!StateMachine)
	{
		return;
	}

	Collider = Player->GetComponent<DWBoxCollider>();

	// 追加したいStateを名前検索して、入れる
	if (DWState* idleState = StateMachine->FindState("PlayerIdle"))
	{
		RelevantStates.push_back(idleState);
	}
	if (DWState* moveState = StateMachine->FindState("PlayerMove"))
	{
		RelevantStates.push_back(moveState);
	}
}

void DWPlayerLand::Enter()
{ 
	if (!Player)
	{
		return;
	}

	Player->Ground();
}

void DWPlayerLand::Update()
{
	NextState();
}

void DWPlayerLand::Exit()
{
}

void DWPlayerLand::NextState()
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

bool DWPlayerLand::IsActive() const
{
	if (!Player)
	{
		return false;
	}

	if (!Collider)
	{
		return false;
	}

	return Collider->GetHitFlagY();
}
