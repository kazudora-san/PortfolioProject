//-----------------------------
//	Section.h[ステージの１区画制御]
//	千葉知輝
//	作成日 2025/10/22
//-----------------------------

#ifndef DWSECTION_H
#define DWSECTION_H

#include "DWManager/DWEnemyManager/DWEnemyManager.h"
#include "DWManager/DWBlockManager/DWBlockManager.h"
#include "DWManager/DWStageManager/DWStageManager.h"
#include "DWVector2/DWVector2.h"
#include "DWMain.h"

constexpr int SectionWidth = 10;
constexpr int SectionHeight = 10;
constexpr DWVector2 TileSize = { 100.0f, 100.0f };

// フィールドを真ん中あたりで生成するための変数
constexpr DWVector2 FieldOffset = {ScreenResolutionWidth / 4.0f, ScreenResolutionHeight / 4.0f};

enum FieldType
{
	None = 0,
	BlockNormal,
	BlockBreak,
	EnemyGround,
};

class DWSection : public DWGameObject
{
private:
	int Section[SectionHeight][SectionWidth] = {};
	DWEnemyManager* EnemyManager = nullptr;
	DWBlockManager* BlockManager = nullptr;
	DWVector2		Offset		= {};

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual void	Reset()	override;
	void CreateSection(int index, const DWVector2& offset);
	void ResetSection(int index, const DWVector2& offset);
};

#endif // SECTION_H
