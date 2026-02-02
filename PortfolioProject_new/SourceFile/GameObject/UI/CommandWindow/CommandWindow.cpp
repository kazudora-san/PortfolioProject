#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"CommandWindow.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Cursor/CursorBase.h"
#include	"Cursor/CommandCursor/CommandCursor.h"
#include	"Input/Input.h"

//---------------------------------------
// フィールドの時のメニューコマンドの処理
//---------------------------------------

// 新しく表示を追加する場合は、MaxFieldCommandを＋１して、
// 座標、画像サイズ、ファイルパスを追加してください
constexpr int		MaxFieldCommand							= 2;
constexpr float		Half									= 2.0f;
constexpr XMFLOAT2	CommandWindowPosition[MaxFieldCommand]	= { {200.0f, 100.0f}, {200.0f, 100.0f} };
constexpr XMFLOAT2	CommandWindowWidth	[MaxFieldCommand]	= { {300.0f, 300.0f}, {300.0f, 150.0f} };
const char*			CommandWindowFileName[MaxFieldCommand]	= {	"Asset\\Texture\\WindowLogo.png",
																"Asset\\Texture\\MenuCommand.png" };

void CommandWindow::Init()
{
	for (int i = 0; i < MaxFieldCommand; i++)
	{
		if (!CommandWindowFileName[i])
		{
			break;
		}

		Polygon2D* UIWindow = new Polygon2D();
		UIWindow->Init(	CommandWindowPosition[i].x - CommandWindowWidth[i].x / Half, 
						CommandWindowPosition[i].y - CommandWindowWidth[i].y / Half,
						CommandWindowWidth[i].x, 
						CommandWindowWidth[i].y,
						CommandWindowFileName[i]);

		m_UIWindows.push_back(UIWindow);
	}

	m_Cursor = new CommandCursor();
	m_Cursor->Init();
}

void CommandWindow::Uninit()
{
	if (m_Cursor)
	{
		m_Cursor->Uninit();
		delete m_Cursor;
		m_Cursor = nullptr;
	}

	UI::Uninit();
}

void CommandWindow::Update()
{
	if (Input::CommandDisp())
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

void CommandWindow::Draw()
{
	if (!GetEnable())
	{
		return;
	}

	UI::Draw();
	m_Cursor->Draw();
}