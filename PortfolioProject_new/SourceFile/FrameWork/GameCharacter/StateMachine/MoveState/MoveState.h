#ifndef		MOVESTATE_H
#define		MOVESTATE_H

#include	"GameCharacter/StateMachine/StateMachine.h"

class MoveState : public StateMachine
{
private:

public:
	MoveState() = default;
	MoveState(GameCharacter* ownerObject);

	virtual void	Enter()		override;
	virtual void	Update()	override;
	virtual void	Exit()		override;

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H