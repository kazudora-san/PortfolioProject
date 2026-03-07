//-----------------------------
//	DWEnemyManager.h[DWEnemyManagerクラス制御]
//	千葉知輝
//	作成日 2025/10/21
//-----------------------------

#ifndef DWENEMYMANAGER_H
#define DWENEMYMANAGER_H

#include "DWManager/DWManager.h"
#include "DWFramework/DWEnemyBase/DWEnemyBase.h"
#include <vector>

class DWEnemyManager : public DWManager
{
private:
	std::vector<DWEnemyBase*> EnemyList = {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;

	void	SetEnemy(const DWVector2& position);
};

#endif // DWENEMYMANAGER_H