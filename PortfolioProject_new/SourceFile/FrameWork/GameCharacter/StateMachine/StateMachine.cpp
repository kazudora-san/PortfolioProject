#include	"StateMachine.h"
#include	"GameCharacter/GameCharacter.h"

StateMachine::StateMachine(GameCharacter* ownerObject)
{
	m_OwnerObject = ownerObject;
}

StateMachine::~StateMachine()
{
	m_OwnerObject = nullptr;
}

void StateMachine::Enter()
{
}

void StateMachine::Update()
{
}

void StateMachine::Exit()
{
}