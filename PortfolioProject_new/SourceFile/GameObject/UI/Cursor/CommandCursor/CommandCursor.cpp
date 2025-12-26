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
	m_CursorPosition	= CmdCursorPosition;
	m_CursorMove		= CmdCursorMove;
	CursorBase::Init();
}

void CommandCursor::Uninit()
{
	CursorBase::Uninit();
}

void CommandCursor::Update()
{
	CursorBase::Update();

	CursorMove();
	Select();
}

void CommandCursor::Draw()
{
	CursorBase::Draw();
}

void CommandCursor::CursorMove()
{
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
}

void CommandCursor::Select()
{
}
