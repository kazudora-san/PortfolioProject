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
	// ステート切り替えは親クラスでやる
	for (auto state : m_States)
	{
		if (!state)
		{
			continue;
		}

		if (state->IsActive())
		{
			// ステート
			m_StateName = state->GetStateName();
			break;
		}
	}
}

void StateMachine::Exit()
{
}