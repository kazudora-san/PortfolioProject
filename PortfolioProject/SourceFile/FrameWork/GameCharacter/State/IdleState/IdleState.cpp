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

}

void IdleState::Exit()
{
}