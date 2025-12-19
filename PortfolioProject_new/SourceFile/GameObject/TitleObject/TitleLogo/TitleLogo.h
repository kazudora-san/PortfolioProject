#ifndef		TITLELOGO_H
#define		TITLELOGO_H

#include	"GameObject.h"

class TitleLogo : public GameObject
{
private:
	Vector3						m_EndPosition	= {};
	Vector3						m_BaseScale		= {};
	Vector3						m_Velocity		= {};
	float						m_SquashPower	= {};
	float						m_Spring		= {}; // ÇŒÇÀÇÃã≠Ç≥
	float						m_Damping		= {};  // å∏êäÅiñÄéCÅj

	ID3D11Buffer*				m_VertexBuffer	= {};

	ID3D11InputLayout*			m_VertexLayOut	= {};
	ID3D11PixelShader*			m_PixelShader	= {};
	ID3D11VertexShader*			m_VertexShader	= {};

	ID3D11ShaderResourceView*	m_Texture		= {};


public:
	void	Init		() {}
	void	Init		(float x, float y, float Width, float Height, const char* FileName);
	void	Uninit		() override;
	void	Update		() override;
	void	Draw		() override;
	void	Render		(Vector3 scale = { 1.0f, 1.0f, 1.0f }) { m_Scale = scale; };
	void	NotRender	() { m_Scale = {}; }
};

#endif // TitleLogo_H