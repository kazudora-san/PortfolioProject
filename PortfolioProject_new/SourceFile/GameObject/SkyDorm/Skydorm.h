#ifndef		SKYDORM_H
#define		SKYDORM_H

#include	"GameObject.h"

class ModelRenderer;

class SkyDorm : public GameObject // 継承
{
private:
	// ポリゴンを描画するのに必要な４つ！

	// 頂点バッファ→GPUに送るためやつ
	ID3D11Buffer*			m_VertexBuffer	= {};
	// 
	ID3D11InputLayout*		m_VertexLayout	= {};
	ID3D11VertexShader*		m_VertexShader	= {};
	ID3D11PixelShader*		m_PixelShader	= {};

	ModelRenderer*			m_ModelRenderer	= {};

public:
	void	Init()		override;
	void	Uninit()	override;
	void	Update()	override;
	void	Draw()		override;

};
#endif 