//-----------------------------
//	DWVector2.cpp[Vectorクラスの制御]
//	千葉知輝
//	作成日 2025/10/02
//-----------------------------

#include "DWVector2.h"
#include <cmath>

float DWVector2::Length() const
{
	// ベクトルの長さを求める
	return sqrtf(x * x + y * y);
}

DWVector2 DWVector2::Normalize() const
{
	// 長さを求めて、正規化する
	float length = Length();
	return { x / length, y / length };
}

DWVector2 DWVector2::Lerp(const DWVector2& start, const DWVector2& end, float time) const
{
	// 線形補間
	return { start.x + (end.x - start.x) * time, start.y + (end.y - start.y) * time };
}

float DWVector2::Dot(const DWVector2& vecA, const DWVector2& vecB) const
{
	// 内積の計算
	return vecA.x * vecB.x + vecA.y * vecB.y ;
}

float DWVector2::Cross(const DWVector2& vecA, const DWVector2& vecB) const
{
	// 外積の計算
	return vecA.x * vecB.y - vecA.y * vecB.x;
}

DWVector2 DWVector2::operator+(const DWVector2& vec)
{
	return { x + vec.x, y + vec.y };
}

DWVector2& DWVector2::operator+=(const DWVector2& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}
