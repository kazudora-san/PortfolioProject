#ifndef		ENEMYBASE_H
#define		ENEMYBASE_H

#include	"GameCharacter/GameCharacter.h"

class EnemyBase : public GameCharacter
{
public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

	virtual void	Attack()	= 0;
	virtual void	Idle()		= 0;
	virtual void	Move()		= 0;
};

#endif // ENEMYBASE_H