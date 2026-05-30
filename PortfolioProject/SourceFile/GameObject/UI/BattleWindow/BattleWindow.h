#pragma once

#include "UI.h"

class BattleCommandCursor;

class BattleWindow : public UI
{
private:
	BattleCommandCursor* m_Cursor = {};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};