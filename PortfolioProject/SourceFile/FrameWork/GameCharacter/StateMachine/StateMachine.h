#ifndef		STATEMACHINE_H
#define		STATEMACHINE_H

#include	<vector>
#include	<memory>

class State;
class GameCharacter;

class StateMachine
{
private:
	std::vector<std::unique_ptr<State>>	m_States		= {};
	State*								m_CurrentState	= {};

public:

	void Update();

	// Å‰‚Í‰½‚à‘€ì‚ğ‚µ‚È‚¢‚Ì‚ÅAIdle‚ğˆê”Ôã‚ÅéŒ¾‚·‚é‚±‚Æ
	template <typename T>
	T* AddState(GameCharacter* owner)
	{
		auto state = std::make_unique<T>(owner);

		T* ptr = state.get();
		m_States.push_back(std::move(state));

		if (!m_CurrentState)
		{
			m_CurrentState = ptr;
		}

		return ptr;
	}

	void	ChangeState(State* state);
};

#endif // STATEMACHINE_H