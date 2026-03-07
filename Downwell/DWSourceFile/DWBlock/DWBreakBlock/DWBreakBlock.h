//-----------------------------
//	BreakBlock.h[壊れるブロック制御]
//	千葉知輝
//	作成日 2025/10/30
//-----------------------------

#ifndef DWBREAKBLOCK_H
#define DWBREAKBLOCK_H

#include "DWBlockBase/DWBlockBase.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"

constexpr float BreakBlockLife = 1;

class DWBreakBlock : public DWBlockBase
{
private:
	float BlockLife = BreakBlockLife; // １発で壊れる

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	SetEnable	(bool enable)	override;

	virtual void	Reset() override;
	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};

#endif // BREAKBLOCK_H
