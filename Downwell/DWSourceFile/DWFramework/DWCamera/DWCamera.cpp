//-----------------------------
//	DWCamera.cpp[ブロック処理]
//	千葉知輝
//	作成日 2025/10/20
//-----------------------------

#include "DWMain.h"
#include "DWCamera.h"

constexpr DWVector2 CameraPosition = { 500.0f, 800.0f };

void DWCamera::Init()
{
	PlayerPosition = Scene->GetGameObject<DWPlayer>();
	if (!PlayerPosition)
	{
		return;
	}

	// プレイヤーをカメラ（Y軸）の中心に持ってくるように調整
	Position.y = PlayerPosition->GetPosition().y - ScreenResolutionHeight / 2.0f;

	Tag = "Camera";
}

void DWCamera::Uninit()
{
	DWGameObject::Uninit();
}

void DWCamera::Update()
{
	if (!Scene || !PlayerPosition)
	{
		return;
	}

	Position.y = PlayerPosition->GetPosition().y - ScreenResolutionHeight / 2.0f;
	Scene->SetOffset(Position);
}

void DWCamera::Draw() const
{
#ifdef _DEBUG
	printfDx("\nCameraPosition Y：%f\n", Position.y);
#endif // _DEBUG

}

void DWCamera::Reset()
{
	Position.y = PlayerPosition->GetPosition().y - ScreenResolutionHeight / 2.0f;
}
