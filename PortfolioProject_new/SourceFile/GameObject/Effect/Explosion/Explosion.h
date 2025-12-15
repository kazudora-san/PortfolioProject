#ifndef		EXPLOSION_H
#define		EXPLOSION_H

#include	"GameObject.h"

class Explosion : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer	= {};

	ID3D11InputLayout*			m_VertexLayOut	= {};
	ID3D11PixelShader*			m_PixelShader	= {};
	ID3D11VertexShader*			m_VertexShader	= {};

	ID3D11ShaderResourceView*	m_Texture		= {};

	XMFLOAT3					position		= {};
	float						rotation		= {};
	int							m_Frame			= {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

};

#endif // EXPLOSION_H