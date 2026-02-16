#include	"StateMachine.h"
#include	"GameCharacter/State/State.h"

void StateMachine::Update()
{
	m_CurrentState->Update();
}

void StateMachine::StateChanege(State* state)
{
	if (m_CurrentState)
	{
		m_CurrentState->Exit();
	}

	m_CurrentState = state;

	if (m_CurrentState)
	{
		m_CurrentState->Enter();
	}
}
