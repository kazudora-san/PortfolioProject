#ifndef MAIN_H
#define MAIN_H

#define		_CRT_SECURE_NO_WARNINGS
#define		NOMINMAX

#include	<stdio.h>

#include	<windows.h>
#include	<assert.h>
#include	<functional>

#include	<d3d11.h>

#pragma comment(lib, "d3d11.lib")


#include	<DirectXMath.h>
using namespace	DirectX;

#include	"Texture/DirectXTex.h"

#include	"Vector3/Vector3.h"

#if _DEBUG
#pragma comment(lib,"DirectXTex_Debug.lib")
#else
#pragma comment(lib,"DirectXTex_Release.lib")
#endif



#pragma comment (lib, "winmm.lib")


#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)


HWND GetWindow();

void Invoke(std::function<void()> Function, int Time);

#endif // MAIN_H