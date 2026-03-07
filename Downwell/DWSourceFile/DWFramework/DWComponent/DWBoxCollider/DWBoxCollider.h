//-----------------------------
//	DWBoxCollider.h[DWBoxColliderクラス制御]
//	千葉知輝
//	作成日 2025/10/15
//-----------------------------

#ifndef DWBOXCOLLIDER_H
#define DWBOXCOLLIDER_H

#include "DWComponent/DWComponent.h"
#include "DWVector2/DWVector2.h"

class DWBoxCollider : public DWComponent
{
private:
	DWVector2 BoundingBoxPosition	= {};
	DWVector2 BoundingBoxScale		= {};
	DWVector2 Overlap				= {};
	bool bIsHit = false;

public:
	DWBoxCollider() = default;
	DWBoxCollider(DWGameObject* gameObject);

	virtual void Init()		override;
	virtual void Uninit()	override;
	virtual void Update()	override;

	void SetBoxPosition	(const DWVector2& position)	{ BoundingBoxPosition	= position; }
	void SetScale		(const DWVector2& scale)	{ BoundingBoxScale		= scale; }

	const DWVector2& GetBoxPosition()	{ return BoundingBoxPosition; }
	const DWVector2& GetScale()			{ return BoundingBoxScale; }

	void SetOverlap	(const DWVector2& overlap)	{ Overlap = overlap; }
	void SetHitFlagY	(bool isHit)				{ bIsHit = isHit; }

	const DWVector2&	GetOverlap()	{ return Overlap; }
	bool				GetHitFlagY()	{ return bIsHit; }

	virtual void	SetEnable(bool enable) override;
};

#endif // DWBOXCOLLIDER_H