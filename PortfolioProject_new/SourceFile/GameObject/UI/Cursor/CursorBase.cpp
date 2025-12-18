#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"CursorBase.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Input/Input.h"

// ScaleÇÕ.hÇ…íuÇ´Ç‹ÇµÇΩ Å¶CommandWindowÇ≈égÇ§ÇΩÇﬂ
constexpr XMFLOAT2	CmdCursorPosition		= { 70.0f, 50.0f};
constexpr XMFLOAT2	CmdCursorMove			= { 130.0f, 50.0f};
constexpr XMFLOAT2	BattleCursorPosition	= { 150.0f, 500.0f };
constexpr XMFLOAT2	BattleCursorMove		= { 0.0f, 50.0f };

void CursorBase::Init()
{
	m_CursorFileName = { "Asset\\Texture\\Cursor.png" };
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