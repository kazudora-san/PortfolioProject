#include	"Idle.h"
#include	"GameCharacter/GameCharacter.h"

IdleState::IdleState(GameCharacter* ownerObject)
{
	m_OwnerObject = ownerObject;

	// m_StateName‚É“ü‚ê‚é‚ÍAm_StateName‚ğg‚¤‚±‚Æ
	m_StateName = "Idle";
}

void IdleState::Enter()
{
	SetStateName(m_StateName);
}

void IdleState::Update()
{
	m_OwnerObject->Idle();
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
	if (m_OwnerObject->GetCharacterStatus().GetHealth() > 0)
	{
		return false;
	}

	return true;
}