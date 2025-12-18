#ifndef		ENEMYBASE_H
#define		ENEMYBASE_H

#include	"GameCharacter/GameCharacter.h"
#include	<string>

class EnemyBase : public GameCharacter
{
protected:


public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

	virtual void	Attack() = 0;
};

#endif // PLAYER_H