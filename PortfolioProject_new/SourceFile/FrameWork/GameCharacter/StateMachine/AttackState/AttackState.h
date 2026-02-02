#ifndef		ATTACKSTATE_H
#define		ATTACKSTATE_H

#include	"GameCharacter/StateMachine/StateMachine.h"

class AttackState : public StateMachine
{
private:

public:
	AttackState() = default;
	AttackState(GameCharacter* ownerObject);

	virtual void	Enter()		override;
	virtual void	Update()	override;
	virtual void	Exit()		override;

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H