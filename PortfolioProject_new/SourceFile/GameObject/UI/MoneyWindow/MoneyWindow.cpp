#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"MoneyWindow/MoneyWindow.h"
#include	"Camera/Camera.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Scene/Scene.h"
#include	"Texture/Texture.h"
#include	"Renderer/Polygon2D/Polygon2D.h"

constexpr XMFLOAT2	MoneyWindowPosition	= { 200.0f, 100.0f };
constexpr XMFLOAT2	MoneyWindowWidth	= { 300.0f, 300.0f };
const char*			MoneyWindowFileName	= {	"Asset\\Texture\\WindowLogo.png"};

void MoneyWindow::Init()
{
	if (!MoneyWindowFileName)
	{
		return;
	}

	Polygon2D* UIWindow = new Polygon2D();
	UIWindow->Init(	MoneyWindowPosition.x - MoneyWindowWidth.x / 2.0f, 
					MoneyWindowPosition.y - MoneyWindowWidth.y / 2.0f,
					MoneyWindowWidth.x, 
					MoneyWindowWidth.y,
					MoneyWindowFileName);

	m_UIWindows.push_back(UIWindow);
}

void MoneyWindow::Uninit()
{
	UI::Uninit();
}

void MoneyWindow::Update()
{
}

void MoneyWindow::Draw()
{
	for (Polygon2D* UIWindow : m_UIWindows)
	{
		if (!UIWindow)
		{
			continue;
		}

		UIWindow->Draw();
	}
}