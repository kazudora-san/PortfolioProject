#ifndef		PLAYERMODEL_H
#define		PLAYERMODEL_H

#include	"Player/Player.h"
#include	<string>

class PlayerModel : public Player
{
private:

	ID3D11InputLayout* m_VertexLayOut;
	ID3D11PixelShader* m_PixelShader;
	ID3D11VertexShader* m_VertexShader;

	//class ModelRenderer* m_ModelRenderer;
	//class ModelRenderer* m_ModelRendererChild;

	class	AnimationModel* m_AnimationModel;
	std::string m_AnimationName;
	std::string m_AnimationNameNext;
	float m_AnimationBlend;

	unsigned int m_Frame;

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

#endif // PLAYERMODEL_H