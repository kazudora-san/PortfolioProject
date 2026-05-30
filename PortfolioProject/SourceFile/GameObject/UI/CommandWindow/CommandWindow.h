#pragma once

#include "UI.h"
#include <vector>

class CommandCursor;

class CommandWindow : public UI
{
private:
	CommandCursor* m_Cursor = {};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};