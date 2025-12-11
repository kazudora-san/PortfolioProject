#ifndef		IDLESTATE_H
#define		IDLESTATE_H

#include	"GameCharacter/StateMachine/StateMachine.h"

class IdleState : public StateMachine
{
protected:


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	virtual bool	IsActive()	const	override;
};

#endif // PLAYER_H