#pragma once

#include	"GameObject.h"
#include	"Vector3/Vector3.h"

constexpr int TitleHeartMax = 10000;

class TitleHeart : public GameObject
{
private:
	struct PARTICLE
	{
		bool Enable = {};
		int Life = {};
		Vector3 Position = {};
		Vector3 Velocity = {};
	};

	PARTICLE m_TitleHeartStart[TitleHeartMax] = {};
	PARTICLE m_TitleHeartEnd[TitleHeartMax] = {};

	ID3D11Buffer* m_VertexBuffer = {};

	ID3D11InputLayout* m_VertexLayout = {};
	ID3D11VertexShader* m_VertexShader = {};
	ID3D11PixelShader* m_PixelShader = {};

	ID3D11ShaderResourceView* m_Texture = {};

	float m_Time = {};

	Vector3 m_StartLine[4] = {};
	Vector3 m_EndLine[4] = {};

	Vector3 m_StartPosition = {};
	Vector3 m_EndPosition = {};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
};