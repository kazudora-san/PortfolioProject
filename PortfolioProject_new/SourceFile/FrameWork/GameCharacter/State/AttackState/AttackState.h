#ifndef		ATTACKSTATE_H
#define		ATTACKSTATE_H

#include	"GameCharacter/State/State.h"

class AttackState : public State
{
private:

public:
	AttackState() = default;
	AttackState(GameCharacter* ownerObject);

	virtual void	Enter()				override;
	virtual void	Update()			override;
	virtual void	Exit()				override;

	virtual bool	IsActive()	const	override;
};

#endif // ATTACKSTATE_H