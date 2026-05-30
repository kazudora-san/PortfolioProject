#include "Main.h"
#include "Renderer/Renderer.h"
#include "Cursor/CommandCursor/CommandCursor.h"
#include "Renderer/Polygon2D/Polygon2D.h"
#include "Input/Input.h"

// Scale‚Í.h‚É’u‚«‚Ü‚µ‚½ ¦CommandWindow‚ÅŽg‚¤‚½‚ß
constexpr XMFLOAT2 CommandCursorPosition = { 70.0f, 50.0f };
constexpr XMFLOAT2 CommandCursorMove = { 130.0f, 50.0f };

void CommandCursor::Init()
{
	m_CursorPosition = CommandCursorPosition;
	m_CursorMove = CommandCursorMove;

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
		if (m_Position.x > CommandCursorPosition.x)
		{
			m_Position.x -= CommandCursorMove.x;
		}
	}

	if (Input::CommandRight())
	{
		if (m_Position.x < CommandCursorMove.x)
		{
			m_Position.x += CommandCursorMove.x;
		}
	}

	if (Input::CommandUp())
	{
		if (m_Position.y > 0.0f)
		{
			m_Position.y -= CommandCursorMove.y;
		}
	}

	if (Input::CommandDown())
	{
		if (m_Position.y < CommandCursorPosition.y + CommandCursorMove.y)
		{
			m_Position.y += CommandCursorMove.y;
		}
	}
}

void CommandCursor::Select()
{
}