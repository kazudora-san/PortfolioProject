//-----------------------------
//	DWTitleLogo.cpp[タイトルロゴ表示処理]
//	千葉知輝
//	作成日 2025/10/31
//-----------------------------

#include "DWMain.h"
#include "DWTitleLogo.h"
#include <string>

constexpr DWVector2 TitleLogoPosition = {ScreenResolutionWidth / 2.0f, ScreenResolutionHeight / 4.0f};
constexpr int TitleLogoTextType = 2;
const std::string TitleLogoText[TitleLogoTextType] = {"DOWNWELL", "Space or RShift to StartGame!"};
constexpr int TitleLineSpace = 10;
constexpr int TitleFontSize = 60;
void DWTitleLogo::Init()
{
	Position = TitleLogoPosition;
	SetFontSize(TitleFontSize);
}

void DWTitleLogo::Uninit()
{
	DWGameObject::Uninit();
}

void DWTitleLogo::Update()
{
	DWGameObject::Update();

	CurrentFrame++;

	if (CurrentFrame > DispFrame)
	{
		DispFlag = !DispFlag;
		CurrentFrame = 0;
	}
}

void DWTitleLogo::Draw() const
{
	DWGameObject::Draw();

	for (int i = 0; i < TitleLogoTextType; i++)
	{
		if (i > 0)
		{
			if (DispFlag)
			{
				continue;
			}
		}
		
		int positionX = GetDrawStringWidth(TitleLogoText[i].c_str(), static_cast<int>(TitleLogoText[i].size()));

		DrawString(static_cast<int>(ScreenResolutionWidth / 2.0f - positionX / 2.0f),
			static_cast<int>(Position.y + (i * GetFontSize() * TitleLineSpace)),
			TitleLogoText[i].c_str(), RedColor);
	}
}

void DWTitleLogo::Reset()
{
	
}

void DWTitleLogo::OnCollision(DWGameObject* gameObject, const DWVector2& overlap)
{
}