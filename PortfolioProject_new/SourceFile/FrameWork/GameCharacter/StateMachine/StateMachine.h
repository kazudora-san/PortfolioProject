#ifndef		STATEMACHINE_H
#define		STATEMACHINE_H

#include	<vector>
#include	<memory>

class State;

class StateMachine
{
private:
	std::vector<std::unique_ptr<State>>	m_States		= {};
	State*								m_CurrentState	= {};

public:
	template <typename T>
	T* AddState(T, Args)
	{
		m_States.push_back();

		return state;
	}

	void	StateChanege(State* state);

};

#endif // STATEMACHINE_H