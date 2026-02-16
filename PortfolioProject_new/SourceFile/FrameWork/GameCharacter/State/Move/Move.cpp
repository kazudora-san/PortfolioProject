#include	"Move.h"
#include	"GameCharacter/GameCharacter.h"
#include	"Input/Input.h"

Move::Move(GameCharacter* ownerObject)
{
	m_OwnerObject	= ownerObject;

	// m_StateName‚É“ü‚ê‚éŽž‚ÍAm_StateName‚ðŽg‚¤‚±‚Æ
	m_StateName		= "Move";
}

void Move::Enter()
{
	SetStateName(m_StateName);
}

void Move::Update()
{
	m_OwnerObject->Move();
}

void Move::Exit()
{
}

bool Move::IsActive() const
{
	if (!m_OwnerObject)
	{
		return false;
	}
	
	if (m_OwnerObject->GetCharacterStatus().GetHealth() > 0 &&
		Input::MoveBack() || Input::MoveFront() ||
		Input::MoveLeft() || Input::MoveRight())
	{
		return true;
	}

	return false;
}
