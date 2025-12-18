#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"CursorBase.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Input/Input.h"

// Scale‚Í.h‚É’u‚«‚Ü‚µ‚½ ¦CommandWindow‚Åg‚¤‚½‚ß
constexpr XMFLOAT2	CmdCursorMove			= { 130.0f, 50.0f};

void CursorBase::Init()
{
	m_CursorFileName	= { "Asset\\Texture\\Cursor.png" };
	m_SelectIndex		= 0;
	UI::Init();
}

void CursorBase::Uninit()
{
	UI::Uninit();
}

void CursorBase::Update()
{
	UI::Update();
}

void CursorBase::Draw()
{
	UI::Draw();
}