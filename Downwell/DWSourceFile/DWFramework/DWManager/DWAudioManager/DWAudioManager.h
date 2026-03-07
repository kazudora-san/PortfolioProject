//-----------------------------
//	DWAudioManager.h[DWAudioManagerクラス制御]
//	千葉知輝
//	作成日 2025/10/31
//-----------------------------

#ifndef DWAUDIOMANAGER_H
#define DWAUDIOMANAGER_H

#include "DWManager/DWManager.h"
#include <map>
#include <tchar.h>

class DWAudioManager : public DWManager
{
private:
	std::map<const TCHAR*, int> BGMList = {};
	std::map<const TCHAR*, int> SEList = {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;

	void	InitLoadTitleAudio();
	void	InitLoadGameAudio();

	void	LoadBGM(const TCHAR* tag, const TCHAR* fileName);
	void	LoadSE(const TCHAR* tag, const TCHAR* fileName);

	void	PlayBGM(const TCHAR* tag);
	void	PlaySE(const TCHAR* tag);

	void	StopBGM(const TCHAR* tag);
	void	StopSE(const TCHAR* tag);

	void	ReStartSE(const TCHAR* tag);
};

#endif // DWAUDIOMANAGER_H