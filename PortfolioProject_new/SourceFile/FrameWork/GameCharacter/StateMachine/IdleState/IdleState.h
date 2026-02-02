#ifndef		IDLESTATE_H
#define		IDLESTATE_H

#include	"GameCharacter/StateMachine/StateMachine.h"

class IdleState : public StateMachine
{
private:

public:
	IdleState() = default;
	IdleState(GameCharacter* ownerObject);

	virtual void	Enter()		override;
	virtual void	Update()	override;
	virtual void	Exit()		override;

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H