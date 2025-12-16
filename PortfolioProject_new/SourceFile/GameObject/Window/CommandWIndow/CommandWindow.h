#ifndef		COMMANDWINDOW_H
#define		COMMANDWINDOW_H

#include	"GameObject.h"

class Polygon2D;

class CommandWindow : public GameObject // 継承
{
private:

	std::vector<Polygon2D>		UITexture		= {};

	// ポリゴンを描画するのに必要な４つ！

	// 頂点バッファ→GPUに送るためやつ
	ID3D11Buffer*				m_VertexBuffer	= {};
	// 
	ID3D11InputLayout*			m_VertexLayout	= {};
	ID3D11VertexShader*			m_VertexShader	= {};
	ID3D11PixelShader*			m_PixelShader	= {};

	ID3D11ShaderResourceView*	m_Texture		= {};

public:
	void	Init()		override;
	void	Uninit()	override;
	void	Update()	override;
	void	Draw()		override;
};

#endif