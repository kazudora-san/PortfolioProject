#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"Cursor/Cursor.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Input/Input.h"

// Scale‚Í.h‚É’u‚«‚Ü‚µ‚½ ¦CommandWindow‚ÅŽg‚¤‚½‚ß
constexpr XMFLOAT2	CursorPosition	= { 70.0f, 50.0f};
constexpr XMFLOAT2	CursorMove		= { 130.0f, 50.0f};
const char*			CursorFileName	= {	"Asset\\Texture\\Cursor.png" };

void Cursor::Init()
{
	if (!CursorFileName)
	{
		return;
	}

	Polygon2D* UIWindow = new Polygon2D();
	UIWindow->Init(	CursorPosition.x - CursorScale.x / 2.0f, 
					CursorPosition.y - CursorScale.y / 2.0f,
					CursorScale.x, 
					CursorScale.y,
					CursorFileName);

	m_UIWindows.push_back(UIWindow);
}

void Cursor::Uninit()
{
	UI::Uninit();
}

void Cursor::Update()
{
	if (Input::CommandLeft())
	{
		if (m_Position.x > CursorPosition.x)
		{
			m_Position.x -= CursorMove.x;
		}
	}
	if (Input::CommandRight())
	{
		if (m_Position.x < CursorMove.x)
		{
			m_Position.x += CursorMove.x;
		}
	}
	if (Input::CommandUp())
	{
		if (m_Position.y > 0.0f)
		{
			m_Position.y -= CursorMove.y;
		}
	}
	if (Input::CommandDown())
	{
		if (m_Position.y < CursorPosition.y + CursorMove.y)
		{
			m_Position.y += CursorMove.y;
		}
	}
	
	for (Polygon2D* cursor : m_UIWindows)
	{
		if (!cursor)
		{
			continue;
		}

		cursor->SetPosition({ m_Position });
	}
}

void Cursor::Draw()
{
	UI::Draw();
}