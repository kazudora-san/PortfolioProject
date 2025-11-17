#ifndef		PLAYER_H
#define		PLAYER_H

#include	"GameObject.h"
#include	<string>

class AnimationModel;
class AudioManager;

class Player : public GameObject
{
private:

	ID3D11InputLayout* m_VertexLayOut;
	ID3D11PixelShader* m_PixelShader;
	ID3D11VertexShader* m_VertexShader;


	//class ModelRenderer* m_ModelRenderer;
	//class ModelRenderer* m_ModelRendererChild;

	class AnimationModel* m_AnimationModel;
	std::string m_AnimationName;
	std::string m_AnimationNameNext;
	float m_AnimationBlend;

	unsigned int m_Frame;

	float m_Jump = 0.0f;
	bool m_IsJump = false;
	float m_JumpTime = 0.0f;

	AudioManager* m_Audio;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

#endif // PLAYER_H