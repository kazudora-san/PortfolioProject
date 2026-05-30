#pragma once

#include "GameObject.h"
#include <string>

class AnimationModel;

class TitleEnemy : public GameObject
{
private:
	ID3D11InputLayout* m_VertexLayOut = {};
	ID3D11PixelShader* m_PixelShader = {};
	ID3D11VertexShader* m_VertexShader = {};

	AnimationModel* m_AnimationModel = {};

	std::string m_AnimationNameNext = {};
	std::string m_AnimationName = {};

	float m_AnimationBlend = {};

	unsigned int m_Frame = {};

public:
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
};