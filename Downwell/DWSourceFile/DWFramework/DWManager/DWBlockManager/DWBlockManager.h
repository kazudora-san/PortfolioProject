//-----------------------------
//	DWBlockManager.h[DWBlockManagerクラス制御]
//	千葉知輝
//	作成日 2025/10/23
//-----------------------------

#ifndef DWBLOCKMANAGER_H
#define DWBLOCKMANAGER_H

#include "DWManager/DWManager.h"
#include "DWBlockBase/DWBlockBase.h"
#include <vector>

enum BlockType
{
	NormalBlock = 0,
	BreakBlock,
};

class DWBlockManager : public DWManager
{
private:
	std::vector<DWBlockBase*> BlockList = {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;

	void	SetBlock(const DWVector2& position, BlockType type);
};

#endif // DWBLOCKMANAGER_H