#ifndef		IDLE_H
#define		IDLE_H

#include	"GameCharacter/State/State.h"

class Idle : public State
{
private:

public:
	Idle() = default;
	Idle(GameCharacter* ownerObject);

	virtual void	Enter()		override;
	virtual void	Update()	override;
	virtual void	Exit()		override;

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H