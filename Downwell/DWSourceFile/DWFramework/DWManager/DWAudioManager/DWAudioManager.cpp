//-----------------------------
//	DWAudioManager.cpp[AudioManagerの処理]
//	千葉知輝
//	作成日 2025/10/31
//-----------------------------

#include "DWAudioManager.h"
#include "DWScene/DWScene.h"
#include "DxLib.h"
#include "DWScene/DWTitleScene/DWTitleScene.h"
#include "DWScene/DWGameScene/DWGameScene.h"

void DWAudioManager::Init()
{
	DWScene* scene = GetScene();
	if (!scene)
	{
		return;
	}

	DWTitleScene* titleScene = dynamic_cast<DWTitleScene*>(scene);
	if (titleScene)
	{
		InitLoadTitleAudio();
		return;
	}

	DWGameScene* gameScene = dynamic_cast<DWGameScene*>(scene);
	if (gameScene)
	{
		InitLoadGameAudio();
		return;
	}
}

void DWAudioManager::Uninit()
{
	InitSoundMem();

	BGMList.clear();
	SEList.clear();
}

void DWAudioManager::Update()
{
}

void DWAudioManager::InitLoadTitleAudio()
{
	LoadSE("Start", "asset\\SE\\Title\\pushStart_SE.mp3");
}

void DWAudioManager::InitLoadGameAudio()
{
	// ここに頻繁に使用するBGM、SEを入れておく
	LoadBGM	("GameBGM",			"asset\\BGM\\gamePlay_BGM.mp3");
	LoadSE	("Jump",			"asset\\SE\\Game\\jump_SE.mp3");
	LoadSE	("Shot",			"asset\\SE\\Game\\shot_SE.mp3");
	LoadSE	("PlayerDamageHit",	"asset\\SE\\Game\\damageHit_SE.mp3");
}

void DWAudioManager::LoadBGM(const TCHAR* tag, const TCHAR* fileName)
{
	BGMList[tag] = LoadSoundMem(fileName);
}

void DWAudioManager::LoadSE(const TCHAR* tag, const TCHAR* fileName)
{
	SEList[tag] = LoadSoundMem(fileName);
}

void DWAudioManager::PlayBGM(const TCHAR* tag)
{
	if (CheckSoundMem(BGMList[tag]))
	{
		return;
	}

	PlaySoundMem(BGMList[tag], DX_PLAYTYPE_BACK);
}

void DWAudioManager::PlaySE(const TCHAR* tag)
{
	if (CheckSoundMem(SEList[tag]))
	{
		return;
	}

	PlaySoundMem(SEList[tag], DX_PLAYTYPE_BACK);
}

void DWAudioManager::StopBGM(const TCHAR* tag)
{
	if (!CheckSoundMem(BGMList[tag]))
	{
		return;
	}

	StopSoundMem(BGMList[tag]);
}

void DWAudioManager::StopSE(const TCHAR* tag)
{
	if (!CheckSoundMem(SEList[tag]))
	{
		return;
	}

	StopSoundMem(SEList[tag]);
}

void DWAudioManager::ReStartSE(const TCHAR* tag)
{
	// 連続で"同じ"効果音を鳴らしたい時に使用する
	StopSoundMem(SEList[tag]);

	PlaySoundMem(SEList[tag], DX_PLAYTYPE_BACK);
}
