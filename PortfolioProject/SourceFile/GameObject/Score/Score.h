#ifndef		SCORE_H
#define		SCORE_H

#include	"GameObject.h"


class Score : public GameObject
{
private:
	int							m_Value;

	ID3D11Buffer*				m_VertexBuffer;

	ID3D11InputLayout*			m_VertexLayOut;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11VertexShader*			m_VertexShader;

	ID3D11ShaderResourceView*	m_Texture;

public:
	void	Init();
	void	Uninit();
	void	Update();
	void	Draw();

	void	AddScore(int value)	{ m_Value += value; }
};

#endif // SCORE_H