#ifndef		GAMECHARACTER_H
#define		GAMECHARACTER_H

#include	"GameObject.h"
#include	<string>

class GameCharacter : public GameObject
{
protected:
	int	Health	= 0;

	ID3D11InputLayout* m_VertexLayOut;
	ID3D11PixelShader* m_PixelShader;
	ID3D11VertexShader* m_VertexShader;


	class AnimationModel* m_AnimationModel;
	std::string m_AnimationName;
	std::string m_AnimationNameNext;
	float m_AnimationBlend;

	unsigned int m_Frame;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // PLAYER_H