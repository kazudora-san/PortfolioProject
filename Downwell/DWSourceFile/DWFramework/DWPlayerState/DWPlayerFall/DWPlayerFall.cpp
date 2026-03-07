//-----------------------------
//	DWPlayerFall.cpp[プレイヤーが落下中の処理]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#include "DWPlayerFall.h"
#include "DWComponent/DWStateMachine/DWStateMachine.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"


DWPlayerFall::DWPlayerFall(DWPlayer* player)
{
	StateName = "PlayerFall";
	Player = player;
}

void DWPlayerFall::Init()
{
	if (!StateMachine)
	{
		return;
	}

	Collider = Player->GetComponent<DWBoxCollider>();

	// 追加したいStateを名前検索して、入れる
	if (DWState* landState = StateMachine->FindState("PlayerLand"))
	{
		RelevantStates.push_back(landState);
	}
	if (DWState* shotState = StateMachine->FindState("PlayerShot"))
	{
		RelevantStates.push_back(shotState);
	}
}

void DWPlayerFall::Enter()
{
}

void DWPlayerFall::Update()
{
	if (!Player)
	{
		return;
	}

	Player->Fall();
	Player->Move();

	NextState();
}

void DWPlayerFall::Exit()
{
}

void DWPlayerFall::NextState()
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

bool DWPlayerFall::IsActive() const
{
	// このステートクラスに移行するかの条件

	// nullチェック
	if (!Player)
	{
		return false;
	}

	if (!Collider)
	{
		return false;
	}

	return (Player->GetHealth() > 0.0f && !Collider->GetHitFlagY());
}
