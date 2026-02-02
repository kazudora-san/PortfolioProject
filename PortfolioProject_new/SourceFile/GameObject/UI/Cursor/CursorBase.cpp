#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"CursorBase.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Input/Input.h"

// Scale‚Í.h‚É’u‚«‚Ü‚µ‚½ ¦CommandWindow‚ÅŽg‚¤‚½‚ß
constexpr XMFLOAT2	CmdCursorMove			= { 130.0f, 50.0f};

void CursorBase::Init()
{
	UI::Init();

	m_CursorFileName	= { "Asset\\Texture\\Cursor.png" };
	m_SelectIndex		= 0;

	Polygon2D* UIWindow = new Polygon2D();
	UIWindow->Init(m_CursorPosition.x - m_CursorMove.x / 2.0f,
		m_CursorPosition.y - m_CursorMove.y / 2.0f,
		m_CursorMove.x,
		m_CursorMove.y,
		m_CursorFileName);

	m_UIWindows.push_back(UIWindow);
}

void CursorBase::Uninit()
{
	UI::Uninit();
}

void CursorBase::Update()
{
	UI::Update();

	for (Polygon2D* cursor : m_UIWindows)
	{
		if (!cursor)
		{
			continue;
		}

		cursor->SetPosition({ m_Position });
	}
}

void CursorBase::Draw()
{
	UI::Draw();
}