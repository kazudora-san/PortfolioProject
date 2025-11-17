#ifndef FADEQUAD_H
#define FADEQUAD_H

#include	"GameObject.h"
#include	<functional>

enum class FadeMode { None, In, Out };

class FadeQuad : public GameObject {
	// リソース
	ID3D11Buffer*				m_VertexBuffer	= nullptr;
	ID3D11InputLayout*			m_VertexLayout	= nullptr;
	ID3D11VertexShader*			m_VertexShader	= nullptr;
	ID3D11PixelShader*			m_PixelShader	= nullptr;
	ID3D11ShaderResourceView*	m_TexWhite		= nullptr; // ← 白1×1を外部ファイルから読み込む

	// 状態
	FadeMode				m_Mode		= FadeMode::None;
	float					m_t			= 0.0f;
	float					m_dur		= 0.6f;
	float					m_alpha		= 0.0f;
	XMFLOAT3				m_color		= { 0,0,0 };
	std::function<void()>	m_onDone	= nullptr;

	void			drawFullScreen	(float alpha, const XMFLOAT3& rgb);
	static float	easeInOutSine	(float x);

public:
	void			Init			()	override;
	void			Uninit			()	override;
	void			Update			()	override;
	void			Draw			()	override;

	void			FadeIn			(float duration = 0.6f, XMFLOAT3 color = { 0,0,0 }, std::function<void()> onDone = {});
	void			FadeOut			(float duration = 0.6f, XMFLOAT3 color = { 0,0,0 }, std::function<void()> onDone = {});
	bool			IsBusy			() const { return m_Mode != FadeMode::None; }
};

#endif // FADEQUAD_H