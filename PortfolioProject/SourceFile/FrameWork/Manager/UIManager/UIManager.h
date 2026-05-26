#pragma once

#include <vector>

class UI;

class UIManager
{
private:
	std::vector<UI*> m_UIs = {};

public:
	void Init();
	void Uninit();
};