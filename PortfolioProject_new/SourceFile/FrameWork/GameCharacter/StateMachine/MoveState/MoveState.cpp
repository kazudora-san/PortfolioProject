#include	"MoveState.h"

MoveState::MoveState(GameCharacter* ownerObject)
{
	m_OwnerObject	= ownerObject;

	// m_StateName‚É“ü‚ê‚é‚ÍAm_MoveStateName‚ğg‚¤‚±‚Æ
	m_StateName		= m_MoveStateName = "Move";
}

void MoveState::Enter()
{
}

void MoveState::Update()
{
}

void MoveState::Exit()
{
}

bool MoveState::IsActive() const
{
	return false;
}
