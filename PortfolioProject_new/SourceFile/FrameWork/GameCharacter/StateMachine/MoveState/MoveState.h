#ifndef		MOVESTATE_H
#define		MOVESTATE_H

#include	"GameCharacter/StateMachine/StateMachine.h"

class MoveState : public StateMachine
{
protected:


public:
	virtual void	Enter()		override;
	virtual void	Update()	override;
	virtual void	Exit()		override;

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H