#include	"State.h"
#include	"GameCharacter/GameCharacter.h"

State::State(GameCharacter* ownerObject)
{
	m_OwnerObject = ownerObject;
}

State::~State()
{
	m_OwnerObject = nullptr;
}