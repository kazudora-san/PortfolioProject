#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"Cursor/CommandCursor/CommandCursor.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Input/Input.h"

// Scale‚Í.h‚É’u‚«‚Ü‚µ‚½ ¦CommandWindow‚ÅŽg‚¤‚½‚ß
constexpr XMFLOAT2	CmdCursorPosition		= { 70.0f, 50.0f};
constexpr XMFLOAT2	CmdCursorMove			= { 130.0f, 50.0f};

void CommandCursor::Init()
{
	CursorBase::Init();
	
	Polygon2D* UIWindow = new Polygon2D();
	UIWindow->Init(	CmdCursorPosition.x - CursorScale.x / 2.0f, 
					CmdCursorPosition.y - CursorScale.y / 2.0f,
					CursorScale.x, 
					CursorScale.y,
					m_CursorFileName);

	m_UIWindows.push_back(UIWindow);
}

void CommandCursor::Uninit()
{
	UI::Uninit();
}

void CommandCursor::Update()
{
	UI::Update();

	if (Input::CommandLeft())
	{
		if (m_Position.x > CmdCursorPosition.x)
		{
			m_Position.x -= CmdCursorMove.x;
		}
	}
	if (Input::CommandRight())
	{
		if (m_Position.x < CmdCursorMove.x)
		{
			m_Position.x += CmdCursorMove.x;
		}
	}
	if (Input::CommandUp())
	{
		if (m_Position.y > 0.0f)
		{
			m_Position.y -= CmdCursorMove.y;
		}
	}
	if (Input::CommandDown())
	{
		if (m_Position.y < CmdCursorPosition.y + CmdCursorMove.y)
		{
			m_Position.y += CmdCursorMove.y;
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

void CommandCursor::Draw()
{
	UI::Draw();
}