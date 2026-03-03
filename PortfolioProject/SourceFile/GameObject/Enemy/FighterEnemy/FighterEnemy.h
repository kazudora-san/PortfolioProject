#ifndef		FIGHTERENEMY_H
#define		FIGHTERENEMY_H

#include	"GameCharacter/EnemyBase/EnemyBase.h"

class AnimationModel;

class FighterEnemy :public EnemyBase
{
private:
	AnimationModel*			m_AnimationModel	= {};
	unsigned int			m_Frame				= {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

	virtual void	Attack()	override;
	virtual void	Idle()		override;
	virtual void	Move()		override;
};

#endif