//-----------------------------
//	DWColliderManager.h[DWColliderManagerクラス制御]
//	千葉知輝
//	作成日 2025/10/17
//-----------------------------

#ifndef DWCOLLIDERMANAGER_H
#define DWCOLLIDERMANAGER_H

#include "DWManager/DWManager.h"
#include "DWGameObject.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"
#include <vector>

class DWColliderManager : public DWManager
{
private:
	std::vector<DWBoxCollider*> ColliderObjectList = {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;

	bool	PushColliderObject	(DWBoxCollider*	colliderObject);
	bool	BoundingBox			(DWBoxCollider*	objectA, DWBoxCollider* objectB);
};

#endif // DWCOLLIDERMANAGER_H