//-----------------------------
//	DWInput.h[DWInput（入力）クラス制御]
//	千葉知輝
//	作成日 2025/10/07
//-----------------------------

#ifndef DWINPUT_H
#define DWINPUT_H

class DWInput
{
private:
	char	CurrentKey[256]		= {};	// 現在のキーを格納
	char	PreviousKey[256]	= {};	// １フレーム前のキーを格納
	unsigned int	PadState			= 0;
	unsigned int	PreviousPadState	= 0;

private:
	bool	GetKeyDown	(int keycode)	const;	// Trigger処理(押した"瞬間")
	bool	GetKeyUp	(int keycode)	const;	// Release処理(離した"瞬間")
	bool	GetActionKeyPad	(int keycode)	const;
	bool	GetActionDownPad(int keycode)	const;

public:
	void	UpdateKey	();						// 現在のキー状態を取得する
	bool	GetLeftMove	()				const;
	bool	GetRightMove()				const;
	bool	GetActionKey	()				const;
	bool	GetActionDown()				const;
	bool	GetTitleKeyDown()				const;
};

#endif // DWINPUT_H