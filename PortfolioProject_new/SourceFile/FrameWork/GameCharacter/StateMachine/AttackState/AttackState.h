#ifndef		ATTACKSTATE_H
#define		ATTACKSTATE_H

#include	"GameCharacter/StateMachine/StateMachine.h"

class AttackState : public StateMachine
{
protected:
	

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H