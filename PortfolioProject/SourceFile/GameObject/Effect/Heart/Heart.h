#ifndef		HEART_H
#define		HEART_H

#include	"GameObject.h"
#include	"Vector3/Vector3.h"


class Heart : public GameObject // 継承
{
private:
	struct PARTICLE
	{
		bool		Enable;		// 使われているか
		int			Life;		// 寿命
		Vector3		Position;	// 座標
		Vector3		Velocity;	// 速度
	};

	static const int			PARTICLE_HEART_MAX	= 10000;
	PARTICLE					m_ParticleHeartStart[PARTICLE_HEART_MAX];
	PARTICLE					m_ParticleHeartEnd	[PARTICLE_HEART_MAX];
	// std::arrayの方が安全性が高い
	
	// ポリゴンを描画するのに必要な４つ！

	// 頂点バッファ→GPUに送るためやつ
	ID3D11Buffer*				m_VertexBuffer = NULL;
	// 
	ID3D11InputLayout*			m_VertexLayout;
	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;

	ID3D11ShaderResourceView*	m_Texture;
	float						m_Time;
	Vector3						m_StartLine[4];
	Vector3						m_EndLine[4];
	Vector3						m_StartPosition;
	Vector3						m_EndPosition;

public:
	void	Init()		override;
	void	Uninit()	override;
	void	Update()	override;
	void	Draw()		override;
};

#endif // HEART_H
