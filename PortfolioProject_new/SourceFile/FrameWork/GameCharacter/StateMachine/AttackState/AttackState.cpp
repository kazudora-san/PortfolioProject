#include	"AttackState.h"

AttackState::AttackState(GameCharacter* ownerObject)
{
	m_OwnerObject	= ownerObject;

	// m_StateName‚É“ü‚ê‚é‚ÍAm_AttackStateName‚ğg‚¤‚±‚Æ
	m_StateName		= "Attack";
}

void AttackState::Enter()
{
}

void AttackState::Update()
{
}

void AttackState::Exit()
{
}

bool AttackState::IsActive() const
{
	
	return false;
}
