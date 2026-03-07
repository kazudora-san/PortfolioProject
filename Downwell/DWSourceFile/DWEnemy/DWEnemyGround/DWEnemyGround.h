//-----------------------------
//	Enemy.h[エネミー制御]
//	千葉知輝
//	作成日 2025/10/21
//-----------------------------

#ifndef DWENEMY_H
#define DWENEMY_H

#include "DWEnemyBase/DWEnemyBase.h"
#include "DWVector2/DWVector2.h"

constexpr DWVector2 EnemyScale = { 100.0f, 100.0f };
constexpr DWVector2 EnemyPosition = { 600.0f, 650.0f };
constexpr DWVector2 EnemyMoveSpeed = { 1.0f, 0.0f };

class DWEnemyGround : public DWEnemyBase
{
private:
	const float GravityFactor = Gravity / GravityScale;	// 落下速度の調整

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	SetEnable(bool enable)	override;

	virtual void	Reset() override;

	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};

#endif // ENEMY_H
