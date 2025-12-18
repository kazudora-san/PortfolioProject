#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"BattleCommandCursor.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Input/Input.h"

constexpr XMFLOAT2	BattleBattleCmdCursorPosition		= { 100.0f, 420.0f };
constexpr XMFLOAT2	BattleBattleCmdCursorMove			= { 0.0f, 50.0f };

void BattleCommandCursor::Init()
{
	CursorBase::Init();

	Polygon2D* UIWindow = new Polygon2D();
	UIWindow->Init(	BattleBattleCmdCursorPosition.x - CursorScale.x / 2.0f, 
					BattleBattleCmdCursorPosition.y - CursorScale.y / 2.0f,
					CursorScale.x, 
					CursorScale.y,
					m_CursorFileName);

	m_UIWindows.push_back(UIWindow);
}

void BattleCommandCursor::Uninit()
{
	UI::Uninit();
}

void BattleCommandCursor::Update()
{
	UI::Update();

	if (Input::CommandUp())
	{
		if (m_Position.y > 0.0f)
		{
			m_Position.y -= BattleBattleCmdCursorMove.y;
		}
	}
	if (Input::CommandDown())
	{
		if (m_Position.y < BattleBattleCmdCursorMove.y * 3.0f)
		{
			m_Position.y += BattleBattleCmdCursorMove.y;
		}
	}

	for (Polygon2D* battlecommandcursor : m_UIWindows)
	{
		if (!battlecommandcursor)
		{
			continue;
		}

		battlecommandcursor->SetPosition({ m_Position });
	}
}

void BattleCommandCursor::Draw()
{
	UI::Draw();
}