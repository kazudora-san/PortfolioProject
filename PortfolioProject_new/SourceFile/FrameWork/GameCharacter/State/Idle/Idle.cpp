#include	"Idle.h"
#include	"GameCharacter/GameCharacter.h"

Idle::Idle(GameCharacter* ownerObject)
{
	m_OwnerObject	= ownerObject;
	
	// m_StateName‚É“ü‚ê‚é‚ÍAm_StateName‚ğg‚¤‚±‚Æ
	m_StateName		= "Idle";
}

void Idle::Enter()
{
	SetStateName(m_StateName);
}

void Idle::Update()
{
	m_OwnerObject->Idle();
}

void Idle::Exit()
{
}

bool Idle::IsActive() const
{
	if (!m_OwnerObject)
	{
		return false;
	}

	// —v‰ü‘P
	if(	m_OwnerObject->GetCharacterStatus().GetHealth() > 0)

	return true;
}