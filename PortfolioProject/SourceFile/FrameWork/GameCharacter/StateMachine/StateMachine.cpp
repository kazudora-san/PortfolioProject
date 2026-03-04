#include	"StateMachine.h"
#include	"GameCharacter/State/State.h"

void StateMachine::Update()
{
	if (!m_CurrentState)
	{
		return;
	}

	m_CurrentState->Update();

	State* nextState = m_CurrentState->GetNextState();
	if (!nextState)
	{
		return;
	}

	ChangeState(nextState);
}

void StateMachine::ChangeState(State* state)
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
