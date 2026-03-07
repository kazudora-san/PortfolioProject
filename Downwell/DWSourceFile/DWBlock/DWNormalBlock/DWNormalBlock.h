//-----------------------------
//	NormalBlock.h[ブロック制御]
//	千葉知輝
//	作成日 2025/10/20
//-----------------------------

#ifndef DWNORMALBLOCK_H
#define DWNORMALBLOCK_H

#include "DWBlockBase/DWBlockBase.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"

class DWNormalBlock : public DWBlockBase
{
private:
	

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	SetEnable	(bool enable)	override;

	virtual void	Reset() override;
	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};

#endif // NORMALBLOCK_H
