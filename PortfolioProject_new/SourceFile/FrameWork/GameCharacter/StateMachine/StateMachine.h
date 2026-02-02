#ifndef		STATEMACHINE_H
#define		STATEMACHINE_H

#include	<vector>
#include	<string>

class GameCharacter;

class StateMachine
{
protected:
	GameCharacter*				m_OwnerObject	= {};
	std::vector<StateMachine*>	m_States		= {};
	std::string					m_StateName		= {};

public:
	StateMachine() = default;
	StateMachine(GameCharacter* ownerObject);

	virtual ~StateMachine();

	virtual void	Enter();
	virtual void	Update();
	virtual void	Exit();

	virtual bool	IsActive()	const = 0;
	const std::string&	GetStateName() const { return m_StateName; }
};

#endif // STATEMACHINE_H