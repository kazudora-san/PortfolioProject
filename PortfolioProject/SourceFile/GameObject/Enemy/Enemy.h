#ifndef		ENEMY_H
#define		ENEMY_H

#include	"GameObject.h"

class Enemy :public GameObject
{
private:

	ID3D11InputLayout*		m_VertexLayOut;
	ID3D11PixelShader*		m_PixelShader;
	ID3D11VertexShader*		m_VertexShader;


	class ModelRenderer*	m_ModelRenderer;

	unsigned int			m_Frame;

public:
	void	Init();
	void	Uninit();
	void	Update();
	void	Draw();

};

#endif