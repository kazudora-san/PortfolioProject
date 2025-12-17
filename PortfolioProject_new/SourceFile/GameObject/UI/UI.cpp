#include	"Main.h"
#include	"UI.h"
#include	"Renderer/Polygon2D/Polygon2D.h"

void UI::Uninit()
{
	for (Polygon2D* UIWindow : m_UIWindows)
	{
		if (!UIWindow)
		{
			continue;
		}

		UIWindow->Uninit();
		delete UIWindow;
		UIWindow = nullptr;
	}
}

void UI::Update()
{
}

void UI::Draw()
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