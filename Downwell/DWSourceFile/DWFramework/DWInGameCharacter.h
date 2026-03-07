//-----------------------------
//	DWInGameCharacter.h[キャラクタークラス制御]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#ifndef DWINGAMECHARACTER_H
#define DWINGAMECHARACTER_H

#include "DWGameObject.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"

constexpr float GravityScale = 20.0f;

class DWInGameCharacter : public DWGameObject
{
protected:
	float		Health		= 0;		// キャラクターの体力
	float		MoveSpeed	= 0.0f;		// 移動量
	const float	Gravity		= 9.8f;
	DWVector2	Velocity	= { 0.0f, 0.0f };
	DWBoxCollider* Collider = nullptr;

public:
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual void	Draw()	const	override;

	void	TakeDamage	(const float damage);							// ダメージ処理

	void	SetVelocity	(const DWVector2& velocity)		{ Velocity = velocity; }

	float				GetHealth	()	const	{ return Health; }		// 体力を取得
	float				GetMoveSpeed()	const	{ return MoveSpeed; }	// 移動量を取得
	const	DWVector2&	GetVelocity	()	const	{ return Velocity; }

	virtual void	SetEnable(bool enable) override;

	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override = 0;
};

#endif // INGAMECHARACTER_H