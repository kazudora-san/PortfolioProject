#pragma once

#include "UI.h"

class Polygon2D;

class MoneyWindow : public UI
{
private:

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};