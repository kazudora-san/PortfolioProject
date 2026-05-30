#pragma once

#include "Cursor/CursorBase.h"

class CommandCursor : public CursorBase
{
private:

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void CursorMove() override;
	void Select() override;
};