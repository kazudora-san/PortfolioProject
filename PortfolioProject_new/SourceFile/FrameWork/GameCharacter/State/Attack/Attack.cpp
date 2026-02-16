#include	"Attack.h"
#include	"GameCharacter/GameCharacter.h"

Attack::Attack(GameCharacter* ownerObject)
{
	m_OwnerObject	= ownerObject;

	// m_StateName‚É“ü‚ê‚éŽž‚ÍAm_StateName‚ðŽg‚¤‚±‚Æ
	m_StateName		= "Attack";
}

void Attack::Enter()
{
	SetStateName(m_StateName);
}

void Attack::Update()
{
	m_OwnerObject->Attack();
}

void Attack::Exit()
{
}

bool Attack::IsActive() const
{
	
	return false;
}
