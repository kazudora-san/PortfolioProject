#pragma once

#include "GameObject.h"
#include "Vector3/Vector3.h"

constexpr int ParticleHeartMax = 10000;

class Heart : public GameObject
{
private:
	struct PARTICLE
	{
		bool Enable = {};
		int Life = {};

		Vector3 Position = {};
		Vector3 Velocity = {};
	};

	PARTICLE m_ParticleHeartStart[ParticleHeartMax] = {};
	PARTICLE m_ParticleHeartEnd[ParticleHeartMax] = {};

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
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
};