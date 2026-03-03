#ifndef		UIMANAGER_H
#define		UIMANAGER_H

#include	<vector>

class UI;

class UIManager
{
private:
	std::vector<UI*>	m_UIs = {};

public:
	void Init	();
	void Uninit	();
	
};

#endif // UIMANAGER_H