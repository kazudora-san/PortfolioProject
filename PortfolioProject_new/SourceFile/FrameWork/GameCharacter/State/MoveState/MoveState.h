#ifndef		MOVESTATE_H
#define		MOVESTATE_H

#include	"GameCharacter/State/State.h"

class MoveState : public State
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

#endif // MOVESTATE_H