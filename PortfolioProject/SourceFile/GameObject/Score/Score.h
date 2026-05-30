#pragma once

#include	"GameObject.h"

class Score : public GameObject
{
private:
	int m_Value = {};

	ID3D11Buffer* m_VertexBuffer = {};

	ID3D11InputLayout* m_VertexLayOut = {};
	ID3D11PixelShader* m_PixelShader = {};
	ID3D11VertexShader* m_VertexShader = {};

	ID3D11ShaderResourceView* m_Texture = {};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void AddScore(int value) { m_Value += value; }
};