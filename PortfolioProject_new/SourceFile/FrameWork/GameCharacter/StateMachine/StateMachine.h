#ifndef		STATEMACHINE_H
#define		STATEMACHINE_H

#include	<string>

class GameCharacter;

class StateMachine
{
protected:
	GameCharacter*		m_OwnerObject	= {};
	std::string			m_StateName		= {};

public:
	StateMachine() = default;
	StateMachine(GameCharacter* ownerObject);

	virtual ~StateMachine();

	virtual void	Enter();
	virtual void	Update();
	virtual void	Exit();

	virtual bool	IsActive()	const = 0;
};

#endif // PLAYER_H