//-----------------------------
//	DWMain.cpp[メイン処理]
//	千葉知輝
//	作成日 2025/10/02
//-----------------------------
#define _CRTDBG_MAP_ALLOC
#include "DWMain.h"
#include "DWScene/DWSceneManager.h"
#ifdef _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// 解像度を指定(現在1920×1080、色素16bit)
	SetGraphMode(ScreenResolutionWidth, ScreenResolutionHeight, 16);
	SetDrawScreen(DX_SCREEN_BACK);
	
	//-------------
	// デバッグ用
	//-------------
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		DWSceneManager sceneManager;
		sceneManager.Init();

		// (仮) ESCで処理を止めるようにしている
		while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
		{
#ifdef _DEBUG
			clsDx();
#endif // _DEBUG


			// 画面をクリア
			ClearDrawScreen();

			sceneManager.Update();
			sceneManager.Draw();

			// 表示更新
			ScreenFlip(); 
		}

		sceneManager.Uninit();
	}
	
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}