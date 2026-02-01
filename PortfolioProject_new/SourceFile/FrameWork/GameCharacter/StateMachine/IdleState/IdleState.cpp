#include	"IdleState.h"

IdleState::IdleState(GameCharacter* ownerObject)
{
	m_OwnerObject = ownerObject;
	
	// m_StateNameに入れる時は、m_IdleStateNameを使うこと
	m_StateName = m_IdleStateName = "Idle";
}

void IdleState::Enter()
{
}

void IdleState::Update()
{
}

void IdleState::Exit()
{
}

bool IdleState::IsActive() const
{
	// プレイヤーが生きてるとき
	// プレイヤーが何も捜査してない時

	return true;
}