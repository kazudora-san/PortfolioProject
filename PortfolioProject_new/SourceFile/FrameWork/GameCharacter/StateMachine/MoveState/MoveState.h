#ifndef		MOVESTATE_H
#define		MOVESTATE_H

#include	"GameCharacter/StateMachine/StateMachine.h"

class MoveState : public StateMachine
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