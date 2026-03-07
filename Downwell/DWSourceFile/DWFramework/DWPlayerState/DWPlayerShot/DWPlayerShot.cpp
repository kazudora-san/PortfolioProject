//-----------------------------
//	DWPlayerShot.cpp[プレイヤーが弾を打つ処理]
//	千葉知輝
//	作成日 2025/10/15
//-----------------------------

#include "DWPlayerShot.h"
#include "DWComponent/DWStateMachine/DWStateMachine.h"


DWPlayerShot::DWPlayerShot(DWPlayer* player)
{
	StateName = "PlayerShot";
	Player = player;
}

void DWPlayerShot::Init()
{
	if (!StateMachine)
	{
		return;
	}

	Collider = Player->GetComponent<DWBoxCollider>();

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

void DWPlayerShot::Enter()
{
	if (!Player)
	{
		return;
	}

	Player->Shot();
	ShotCurrentFrame = 0;
}

void DWPlayerShot::Update()
{
	ShotCurrentFrame++;

	if (Collider)
	{
		if (Collider->GetHitFlagY())
		{
			NextState();
			return;
		}
	}

	if (Player)
	{
		Player->Move();

		const DWInput* input = GetInput();

		if (input)
		{
			if (Player && input->GetActionKey() &&
				Player->GetCurrentAmmo() > 0)
			{
				if (ShotCurrentFrame > ShotIntervalFrame)
				{
					Player->Shot();
					ShotCurrentFrame = 0;
				}

				return;
			}
		}
	}

	NextState();
}

void DWPlayerShot::Exit()
{
}

void DWPlayerShot::NextState()
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

bool DWPlayerShot::IsActive() const
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
			Player->GetCurrentAmmo() > 0 &&
			input->GetActionDown());
}
