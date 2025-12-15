#ifndef		TITLEPLAYER_H
#define		TITLEPLAYER_H

#include	"GameObject.h"
#include	<string>

class AudioManager;
class MeshField;

class TitlePlayer : public GameObject
{
private:
	MeshField*				m_MeshField			= {};
	class AnimationModel*	m_AnimationModel	= {};
	std::string				m_AnimationName		= {};
	std::string				m_AnimationNameNext	= {};
	float					m_AnimationBlend	= {};

	ID3D11InputLayout*		m_VertexLayOut		= {};
	ID3D11PixelShader*		m_PixelShader		= {};
	ID3D11VertexShader*		m_VertexShader		= {};

	int						m_Frame				= {};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

#endif // TITLEPLAYER_H