#include	"MoveState.h"
#include	"GameCharacter/GameCharacter.h"
#include	"Input/Input.h"

MoveState::MoveState(GameCharacter* ownerObject)
{
	m_OwnerObject	= ownerObject;

	// m_StateName‚É“ü‚ê‚éŽž‚ÍAm_StateName‚ðŽg‚¤‚±‚Æ
	m_StateName		= "Move";
}

void MoveState::Enter()
{
	SetStateName(m_StateName);
}

void MoveState::Update()
{
	m_OwnerObject->Move();
}

void MoveState::Exit()
{
}

bool MoveState::IsActive() const
{
	if (!m_OwnerObject)
	{
		return false;
	}
	
	if (m_OwnerObject->GetCharacterStatus().GetHealth() > 0 &&
											Input::MoveBack() ||
											Input::MoveFront() ||
											Input::MoveLeft() ||
											Input::MoveRight())
	{
		return true;
	}

	return false;
}
