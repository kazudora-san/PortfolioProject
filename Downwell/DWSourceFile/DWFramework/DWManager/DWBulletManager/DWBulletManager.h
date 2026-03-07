//-----------------------------
//	DWBulletManager.h[DWBulletManagerクラス制御]
//	千葉知輝
//	作成日 2025/10/17
//-----------------------------

#ifndef DWBULLETMANAGER_H
#define DWBULLETMANAGER_H

#include "DWManager/DWManager.h"
#include "DWBullet/DWBullet.h"
#include <vector>

class DWBulletManager : public DWManager
{
private:
	std::vector<DWBullet*> BulletList = {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;

	void	SetBullet(const DWVector2& position);
};

#endif // DWBULLETMANAGER_H