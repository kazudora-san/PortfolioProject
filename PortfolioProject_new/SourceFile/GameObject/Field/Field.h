#ifndef		FIELD_H
#define		FIELD_H

#include "GameObject.h"

class Field: public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer;

	ID3D11InputLayout*			m_VertexLayOut;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11VertexShader*			m_VertexShader;

	ID3D11ShaderResourceView*	m_Texture;
	ID3D11ShaderResourceView*	m_TextureSoil;

	XMFLOAT3					position{0.0f,0.0f,0.0f};
	float						rotation;

public:
	void	Init();
	void	Uninit();
	void	Update();
	void	Draw();
};

#endif