#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"BattleWindow.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Cursor/BattleCommandCursor/BattleCommandCursor.h"
#include	"Input/Input.h"

// 新しく表示を追加する場合は、MaxFieldCommandを＋１して、
// 座標、画像サイズ、ファイルパスを追加してください
constexpr int		MaxFieldCommand							= 2;
constexpr float		Half									= 2.0f;
constexpr XMFLOAT2	BattleWindowPosition[MaxFieldCommand]	= { {150.0f, 500.0f}, {150.0f, 500.0f} };
constexpr XMFLOAT2	BattleWindowWidth	[MaxFieldCommand]	= { {150.0f, 500.0f}, {200.0f, 250.0f} };
const char*			BattleWindowFileName[MaxFieldCommand]	= {	"Asset\\Texture\\WindowLogo.png",
																"Asset\\Texture\\BattleCommand.png" };

void BattleWindow::Init()
{
	for (int i = 0; i < MaxFieldCommand; i++)
	{
		if (!BattleWindowFileName[i])
		{
			break;
		}

		Polygon2D* UIWindow = new Polygon2D();
		UIWindow->Init(	BattleWindowPosition[i].x - BattleWindowWidth[i].x / Half, 
						BattleWindowPosition[i].y - BattleWindowWidth[i].y / Half,
						BattleWindowWidth[i].x, 
						BattleWindowWidth[i].y,
						BattleWindowFileName[i]);

		m_UIWindows.push_back(UIWindow);
	}

	m_Cursor = new BattleCommandCursor();
	m_Cursor->Init();
}

void BattleWindow::Uninit()
{
	if (m_Cursor)
	{
		m_Cursor->Uninit();
		delete m_Cursor;
		m_Cursor = nullptr;
	}

	UI::Uninit();
}

void BattleWindow::Update()
{
	if (Input::BattleWindow())
	{
		SetEnable(true);
	}
	if (Input::CommandCancel())
	{
		SetEnable(false);
		return;
	}

	if (!GetEnable() || !m_Cursor)
	{
		return;
	}

	m_Cursor->Update();
}

void BattleWindow::Draw()
{
	if (!GetEnable())
	{
		return;
	}

	UI::Draw();
	m_Cursor->Draw();
}