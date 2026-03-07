//-----------------------------
//	DWVector2.h[Vectorクラス制御]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

//*******************************************
// XMFLOATを使うのではなく、DWVector2を使う
//*******************************************

#ifndef DWVECTOR2_H
#define DWVECTOR2_H

class DWVector2
{
public:
	float x = 0.0f;	// 座標ｘ
	float y = 0.0f;	// 座標ｙ

public:
	float				Length		()	const;																// ベクトルの長さを求める
	DWVector2			Normalize	()	const;																// 長さを求めて、正規化する
	DWVector2			Lerp		(const DWVector2& start,	const DWVector2& end,	float time) const;	// 線形補間(1 - t的なもの)
	float				Dot			(const DWVector2& vecA,		const DWVector2& vecB)	const;								// 内積の計算
	float				Cross		(const DWVector2& vecA,		const DWVector2& vecB)	const;								// 外積の計算
	DWVector2	operator+(const DWVector2& vec);
	DWVector2& operator+=(const DWVector2& vec);
};

#endif 