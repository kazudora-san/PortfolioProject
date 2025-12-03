#pragma once

#include "Scene/Scene.h"
#include <string>

class AudioManager;
class AnimationModel;

class Title :public Scene
{
private:
	ID3D11Buffer*				m_VertexBuffer;

	ID3D11InputLayout*			m_VertexLayOut;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11VertexShader*			m_VertexShader;

	ID3D11ShaderResourceView*	m_Texture;

	XMFLOAT3					position;
	float						rotation;

	AnimationModel*				m_AnimationModel	= {};
	std::string					m_AnimationName		= {};
	std::string					m_AnimationNameNext	= {};
	float						m_AnimationBlend	= 0;

	unsigned int				m_Frame			= 0;
	unsigned int				m_StopFrame		= 120;
	bool						m_IsNextScene	= false;

	AudioManager*				m_Audio			= nullptr;

public:
	void	Init()		override;
	void	Update()	override;

};