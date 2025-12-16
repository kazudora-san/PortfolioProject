#ifndef		WINDOW_H
#define		WINDOW_H

#include	"GameObject.h"

class Window : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer	= {};

	ID3D11InputLayout*			m_VertexLayOut	= {};
	ID3D11PixelShader*			m_PixelShader	= {};
	ID3D11VertexShader*			m_VertexShader	= {};

	ID3D11ShaderResourceView* m_Texture			= {};


public:
	void	Init		() {}
	void	Init		(float x, float y, float Width, float Height, const char* FileName);
	void	Uninit		();
	void	Update		();
	void	Draw		();
	void	Render		(Vector3 scale = { 1.0f, 1.0f, 1.0f }) { m_Scale = scale; };
	void	NotRender	() { m_Scale = {}; }
};

#endif // WINDOW_H