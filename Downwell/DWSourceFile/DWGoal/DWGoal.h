//-----------------------------
//	Goal.h[ÉSÅ[Éãêßå‰]
//	êÁótímãP
//	çÏê¨ì˙ 2025/10/28
//-----------------------------

#ifndef DWGOAL_H
#define DWGOAL_H

#include "DWGameObject.h"
#include "DWVector2/DWVector2.h"
#include "DWManager/DWStageManager/DWStageManager.h"
#include "DWComponent/DWBoxCollider/DWBoxCollider.h"

constexpr DWVector2 GoalScale = { SectionWidth * TileSize.x, 50.0f };

class DWGoal : public DWGameObject
{
private:
	bool	bIsGoal = false;
	DWBoxCollider* Collider = nullptr;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	Reset() override;
	void SetGoalFlag(bool goalFlag) { bIsGoal = goalFlag; }
	bool GetGoalFlag()	const { return bIsGoal; }
	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};
#endif // PLAYER_H
