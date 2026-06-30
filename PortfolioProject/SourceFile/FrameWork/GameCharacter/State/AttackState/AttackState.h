#pragma once

#include "GameCharacter/State/State.h"

class AttackState : public State
{
private:

public:
	AttackState() = default;
	AttackState(GameCharacter* ownerObject);

	virtual void Enter() override;
	virtual void Update() override;
	virtual void Exit() override;
};