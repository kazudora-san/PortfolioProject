#ifndef		EXPLOSION_H
#define		EXPLOSION_H

#include	"GameObject.h"

class Explosion : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer;

	ID3D11InputLayout*			m_VertexLayOut;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11VertexShader*			m_VertexShader;

	ID3D11ShaderResourceView*	m_Texture;

	XMFLOAT3					position{ 0.0f,0.0f,0.0f };
	float						rotation;
	int							m_Frame;

public:
	void	Init();
	void	Uninit();
	void	Update();
	void	Draw();

};

#endif // EXPLOSION_H