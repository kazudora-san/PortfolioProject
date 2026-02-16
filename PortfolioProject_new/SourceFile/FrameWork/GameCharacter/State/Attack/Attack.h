#ifndef		ATTACK_H
#define		ATTACK_H

#include	"GameCharacter/State/State.h"

class Attack : public State
{
private:

public:
	Attack() = default;
	Attack(GameCharacter* ownerObject);

	virtual void	Enter()		override;
	virtual void	Update()	override;
	virtual void	Exit()		override;

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H