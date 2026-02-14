#include	"StateMachine.h"
#include	"GameCharacter/State/State.h"

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
