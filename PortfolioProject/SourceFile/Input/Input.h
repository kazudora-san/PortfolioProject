#ifndef		INPUT_H
#define		INPUT_H

#include	<windows.h>

class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	static inline LONG mouseDX = 0;
	static inline LONG mouseDY = 0;

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	static void OnMouseMove(LONG dx, LONG dy);

	static LONG GetMouseDX() { return mouseDX; };
	static LONG GetMouseDY() { return mouseDY; };
};

#endif // INPUT_H