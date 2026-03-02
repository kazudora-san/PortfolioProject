#include	"IdleState.h"
#include	"GameCharacter/GameCharacter.h"

IdleState::IdleState(GameCharacter* ownerObject)
{
	m_OwnerObject = ownerObject;

	// m_StateName‚É“ü‚ê‚éŽž‚ÍAm_StateName‚ðŽg‚¤‚±‚Æ
	m_StateName = "Idle";
}

void IdleState::Enter()
{
	SetStateName(m_StateName);
}

void IdleState::Update()
{
	m_OwnerObject->Idle();

	if (ChangeState() ? )
	{
		// —á‚¦‚ÎAMoveState‚É‘JˆÚ‚·‚éê‡
		// m_StateMachine->ChangeState<MoveState>();
	}
}

void IdleState::Exit()
{
}

bool IdleState::IsActive() const
{
	if (!m_OwnerObject)
	{
		return false;
	}

	// —v‰ü‘P
	if (m_OwnerObject->GetCharacterStatus().GetHealth() < 0)
	{
		return false;
	}

	return true;
}