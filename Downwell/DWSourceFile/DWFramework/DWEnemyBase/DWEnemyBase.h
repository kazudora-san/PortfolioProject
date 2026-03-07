//-----------------------------
//	EnemyBase.h[エネミーの親クラス制御]
//	千葉知輝
//	作成日 2025/10/21
//-----------------------------

#ifndef DWENEMYBASE_H
#define DWENEMYBASE_H

#include "DWInGameCharacter.h"
#include "DWVector2/DWVector2.h"

class DWEnemyBase : public DWInGameCharacter
{
protected:
	DWVector2	MoveSpeed			= {};	// 進む方向

public:
	virtual	void	Init()			override = 0;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	SetEnable	(bool enable)	override;

	virtual void	Reset()	override = 0;
	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override = 0;
};

#endif // ENEMY_H
