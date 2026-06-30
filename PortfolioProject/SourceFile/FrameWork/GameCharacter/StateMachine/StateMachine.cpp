#include "StateMachine.h"
#include "GameCharacter/State/State.h"

void StateMachine::Update()
{
    if (!m_CurrentState) return;

    for (auto& transition : m_Transitions)
    {
        // 現在のStateと登録されてあるState＋その関数がtrueであるか
        if (transition.from == m_CurrentState && transition.condition())
        {
            // 事前に登録してあるStateに遷移する
            ChangeState(transition.to);
            break;
        }
    }

    m_CurrentState->Update();
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