#ifndef INPUT_H
#define INPUT_H

#include <windows.h>

//----------------------------------
// ÉLÅ[ì¸óÕÇÕInput.cppì‡ÇÃÇ›Ç≈åƒÇ‘ÇÊÇ§Ç…
// äOïîÇ©ÇÁÇÕä÷êîÇçÏÇ¡ÇƒÇªÇÍÇåƒÇÒÇ≈Ç≠ÇæÇ≥Ç¢
//----------------------------------
constexpr auto KEY_A = (0x41);
constexpr auto KEY_B = (0x42);
constexpr auto KEY_C = (0x43);
constexpr auto KEY_D = (0x44);
constexpr auto KEY_E = (0x45);
constexpr auto KEY_F = (0x46);
constexpr auto KEY_G = (0x47);
constexpr auto KEY_H = (0x48);
constexpr auto KEY_I = (0x49);
constexpr auto KEY_J = (0x4A);
constexpr auto KEY_K = (0x4B);
constexpr auto KEY_L = (0x4C);
constexpr auto KEY_M = (0x4D);
constexpr auto KEY_N = (0x4E);
constexpr auto KEY_O = (0x4F);
constexpr auto KEY_P = (0x50);
constexpr auto KEY_Q = (0x51);
constexpr auto KEY_R = (0x52);
constexpr auto KEY_S = (0x53);
constexpr auto KEY_T = (0x54);
constexpr auto KEY_U = (0x55);
constexpr auto KEY_V = (0x56);
constexpr auto KEY_W = (0x57);
constexpr auto KEY_X = (0x58);
constexpr auto KEY_Y = (0x59);
constexpr auto KEY_Z = (0x5A);
constexpr auto KEY_0 = (0x30);
constexpr auto KEY_1 = (0x31);
constexpr auto KEY_2 = (0x32);
constexpr auto KEY_3 = (0x33);
constexpr auto KEY_4 = (0x34);
constexpr auto KEY_5 = (0x35);
constexpr auto KEY_6 = (0x36);
constexpr auto KEY_7 = (0x37);
constexpr auto KEY_8 = (0x38);
constexpr auto KEY_9 = (0x39);

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
	static bool MoveLeft();
	static bool MoveRight();
	static bool MoveFront();
	static bool MoveBack();

	static bool CommandLeft();
	static bool CommandRight();
	static bool CommandUp();
	static bool CommandDown();

	static bool CommandAction();
	static bool CommandJump();
	static bool CommandDecision();
	static bool CommandCancel();
	static bool CommandDisp();
	static bool BattleWindow();

	static void OnMouseMove(LONG dx, LONG dy);

	static LONG GetMouseDX() { return mouseDX; }
	static LONG GetMouseDY() { return mouseDY; }
};

#endif // INPUT_H