//-----------------------------
//	Bullet.h[íeêßå‰]
//	êÁótímãP
//	çÏê¨ì˙ 2025/10/16
//-----------------------------

#ifndef DWBULLET_H
#define DWBULLET_H

#include "DWGameObject.h"
#include "DWVector2/DWVector2.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"

constexpr int BulletLife = 60;
constexpr DWVector2 BulletMoveSpeed = { 0.0f, 10.0f };
constexpr DWVector2 BulletScale = { 50.0f, 50.0f };

class DWBullet : public DWGameObject
{
private:
	int					Life		= BulletLife;
	const DWVector2&	MoveSpeed	= BulletMoveSpeed;
	DWBoxCollider*		Collider	= nullptr;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	SetEnable(bool enable)	override;
	virtual void	Reset()	override;
	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};
#endif // PLAYER_H
