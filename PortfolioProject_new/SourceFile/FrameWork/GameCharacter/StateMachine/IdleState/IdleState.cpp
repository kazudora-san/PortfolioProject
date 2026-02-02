#include	"IdleState.h"
#include	"GameCharacter/GameCharacter.h"

IdleState::IdleState(GameCharacter* ownerObject)
{
	m_OwnerObject	= ownerObject;
	
	// m_StateName‚É“ü‚ê‚é‚ÍAm_IdleStateName‚ğg‚¤‚±‚Æ
	m_StateName		= "Idle";
}

void IdleState::Enter()
{
}

void IdleState::Update()
{
}

void IdleState::Exit()
{
}

bool IdleState::IsActive() const
{
	if (!m_OwnerObject)
	{
		return;
	}

	// —v‰ü‘P
	if(	m_OwnerObject->GetCharacterStatus().GetHealth() > 0)

	return true;
}