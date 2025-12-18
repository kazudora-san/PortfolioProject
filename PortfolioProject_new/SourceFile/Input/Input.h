#ifndef		INPUT_H
#define		INPUT_H

#include	<windows.h>

#define		KEY_A	(0x41)
#define		KEY_B	(0x42)
#define		KEY_C	(0x43)
#define		KEY_D	(0x44)
#define		KEY_E	(0x45)
#define		KEY_F	(0x46)
#define		KEY_G	(0x47)
#define		KEY_H	(0x48)
#define		KEY_I	(0x49)
#define		KEY_J	(0x4A)
#define		KEY_K	(0x4B)
#define		KEY_L	(0x4C)
#define		KEY_M	(0x4D)
#define		KEY_N	(0x4E)
#define		KEY_O	(0x4F)
#define		KEY_P	(0x50)
#define		KEY_Q	(0x51)
#define		KEY_R	(0x52)
#define		KEY_S	(0x53)
#define		KEY_T	(0x54)
#define		KEY_U	(0x55)
#define		KEY_V	(0x56)
#define		KEY_W	(0x57)
#define		KEY_X	(0x58)
#define		KEY_Y	(0x59)
#define		KEY_Z	(0x5A)
#define		KEY_0	(0x30)
#define		KEY_1	(0x31)
#define		KEY_2	(0x32)
#define		KEY_3	(0x33)
#define		KEY_4	(0x34)
#define		KEY_5	(0x35)
#define		KEY_6	(0x36)
#define		KEY_7	(0x37)
#define		KEY_8	(0x38)
#define		KEY_9	(0x39)

class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	static inline LONG mouseDX = {};
	static inline LONG mouseDY = {};

public:
	static void Init();
	static void Uninit();
	static void Update();

private:
	static bool GetKeyPress(BYTE KeyCode);
	static bool GetKeyTrigger(BYTE KeyCode);
	

public:
	// プレイヤーの移動
	static bool	MoveLeft();
	static bool	MoveRight();
	static bool	MoveFront();
	static bool	MoveBack();

	// コマンドの移動
	static bool	CommandLeft();
	static bool	CommandRight();
	static bool	CommandUp();
	static bool	CommandDown();

	static bool	CommandAction();	// 攻撃
	static bool	CommandJump();		// ジャンプ
	static bool	CommandDecision();	// 決定
	static bool CommandCancel();	// 一つ前に戻る
	static bool CommandDisp();		// メニューコマンド表示
	static bool	BattleWindow();		// バトルコマンド表示

	static void OnMouseMove(LONG dx, LONG dy);

	static LONG GetMouseDX() { return mouseDX; };
	static LONG GetMouseDY() { return mouseDY; };
};

#endif // INPUT_H