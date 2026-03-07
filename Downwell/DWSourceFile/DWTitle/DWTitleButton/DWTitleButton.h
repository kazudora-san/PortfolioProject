//-----------------------------
//	TitleButton.h[タイトルpushボタン制御]
//	千葉知輝
//	作成日 2025/10/31
//-----------------------------

#ifndef DWTITLEBUTTON_H
#define DWTITLEBUTTON_H

#include "DWGameObject.h"

class DWInput;

constexpr int WaitFrameCount = 120;

class DWTitleButton : public DWGameObject
{
private:
	DWInput*	Input	=	nullptr;
	bool		bPushActionKey	= false;
	const	int	WaitFrame		= WaitFrameCount;
	int			CurrentFrame	= 0;

public:
	virtual	void	Init()			override;
	virtual	void	Uninit()		override;
	virtual	void	Update()		override;
	virtual	void	Draw()	const	override;

	virtual	void	Reset()			override;

	virtual void OnCollision(DWGameObject* gameObject, const DWVector2& overlap) override;
};

#endif // TITLEBUTTON_H
