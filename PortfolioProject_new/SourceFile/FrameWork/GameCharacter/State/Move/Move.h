#ifndef		MOVE_H
#define		MOVE_H

#include	"GameCharacter/State/State.h"

class Move : public State
{
private:

public:
	Move() = default;
	Move(GameCharacter* ownerObject);

	virtual void	Enter()		override;
	virtual void	Update()	override;
	virtual void	Exit()		override;

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H