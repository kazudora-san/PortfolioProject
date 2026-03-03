#include	"AttackState.h"
#include	"GameCharacter/GameCharacter.h"

AttackState::AttackState(GameCharacter* ownerObject)
{
	m_OwnerObject	= ownerObject;

	// m_StateName‚É“ü‚ê‚éŽž‚ÍAm_StateName‚ðŽg‚¤‚±‚Æ
	m_StateName		= "Attack";
}

void AttackState::Enter()
{
	SetStateName(m_StateName);
}

void AttackState::Update()
{
	m_OwnerObject->Attack();
}

void AttackState::Exit()
{
}

bool AttackState::IsActive() const
{
	
	return false;
}
