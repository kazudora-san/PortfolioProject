#pragma once

#include	"GameObject.h"

class TitleCamera : public GameObject
{
private:
	XMMATRIX m_MtxView = {};
	XMMATRIX m_MtxPerspective = {};

	Vector3 m_Target = {};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	XMMATRIX GetViewMatrix() { return m_MtxView; }

	Vector3 GetForward() override;
};