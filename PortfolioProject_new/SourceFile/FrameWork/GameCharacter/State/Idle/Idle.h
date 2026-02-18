#ifndef		IDLE_H
#define		IDLE_H

#include	"GameCharacter/State/State.h"

class IdleState : public State
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