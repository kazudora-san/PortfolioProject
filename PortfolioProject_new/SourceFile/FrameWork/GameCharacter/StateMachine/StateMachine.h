#ifndef		STATEMACHINE_H
#define		STATEMACHINE_H

#include	"GameCharacter/GameCharacter.h"
#include	<string>

class StateMachine : public GameCharacter
{
protected:
	GameCharacter*		m_OwnerObject	= nullptr;
	std::string			m_StateName		= {};

public:
	StateMachine() = default;
	StateMachine(GameCharacter* ownerObject);

	virtual void	Init()		;
	virtual void	Uninit()	;
	virtual void	Update()	;
	virtual void	Draw()		;

	virtual bool	IsActive()	const = 0;
};

#endif // PLAYER_H