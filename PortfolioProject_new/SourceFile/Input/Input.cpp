#include	"Main.h"
#include	"Input/Input.h"

#define	TRUEINPUT	(0x80)

BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];


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

void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );

	mouseDX = 0;
	mouseDY = 0;
}

void Input::Uninit()
{


}

void Input::Update()
{

	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );

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

void Input::OnMouseMove(LONG dx, LONG dy)
{
	mouseDX = dx;
	mouseDY = dy;
}

bool Input::Decision()
{
	return GetKeyTrigger(VK_RETURN);
}

bool Input::FieldMenuDisp()
{
	return	(	GetKeyTrigger(KEY_M)||
				CommandUp()			|| CommandDown()	||
				CommandRight()		|| CommandLeft());
}

bool Input::CommandMove()
{
	return (CommandUp() || CommandDown() ||
			CommandRight() || CommandLeft());
}
