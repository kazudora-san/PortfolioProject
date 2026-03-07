//-----------------------------
//	TitleLogo.h[タイトルロゴ表示制御]
//	千葉知輝
//	作成日 2025/10/31
//-----------------------------

#ifndef DWTITLELOGO_H
#define DWTITLELOGO_H

#include "DWGameObject.h"
#include "DWMain.h"

constexpr int ChangeDispFlagFrame = 180;

class DWTitleLogo : public DWGameObject
{
private:
	const int	RedColor		= GetColor(255, 0, 0);
	const int	DispFrame		= ChangeDispFlagFrame;
	int			CurrentFrame	= 0;
	bool		DispFlag		= true;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual	void	Reset()			override;

	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};

#endif // TITLELOGO_H
