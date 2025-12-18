#include	"Main.h"
#include	"Input/Input.h"

#define	TRUEINPUT	(0x80)

BYTE Input::m_OldKeyState[256]	= {};
BYTE Input::m_KeyState[256]		= {};

void Input::Init()
{
	memset(m_OldKeyState, 0, 256);
	memset(m_KeyState, 0, 256);

	mouseDX = 0;
	mouseDY = 0;
}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy(m_OldKeyState, m_KeyState, 256);

	(void)GetKeyboardState(m_KeyState);

	if (GetActiveWindow() != GetWindow())
	{
		mouseDX = 0;
		mouseDY = 0;
	}
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::CommandLeft()
{
	return GetKeyTrigger(VK_LEFT);
}

bool Input::CommandRight()
{
	return GetKeyTrigger(VK_RIGHT);
}

bool Input::CommandUp()
{
	return GetKeyTrigger(VK_UP);
}

bool Input::CommandDown()
{
	return GetKeyTrigger(VK_DOWN);
}

bool Input::CommandAction()
{
	return GetKeyTrigger(VK_SPACE);
}

bool Input::CommandJump()
{
	return GetKeyTrigger(KEY_F);
}

bool Input::CommandDecision()
{
	return GetKeyTrigger(VK_RETURN);
}

bool Input::CommandCancel()
{
	return GetKeyTrigger(VK_BACK);
}

bool Input::CommandDisp()
{
	return GetKeyTrigger(KEY_M);
}

bool Input::BattleWindow()
{
	return GetKeyTrigger(KEY_B);
}

bool Input::MoveLeft()
{
	return GetKeyPress(KEY_A);
}

bool Input::MoveRight()
{
	return GetKeyPress(KEY_D);
}

bool Input::MoveFront()
{
	return GetKeyPress(KEY_W);
}

bool Input::MoveBack()
{
	return GetKeyPress(KEY_S);
}

void Input::OnMouseMove(LONG dx, LONG dy)
{
	mouseDX = dx;
	mouseDY = dy;
}