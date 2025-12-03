#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

class Camera : public GameObject
{
private:
	XMMATRIX	m_MtxView			= {};
	XMMATRIX	m_MtxPerspective	= {};

	Vector3		m_Target			= { 0.0f,0.0f,1.0f };

public:
	void		Init();
	void		Uninit();
	void		Update();
	void		Draw();

	XMMATRIX	GetViewMatrix() { return m_MtxView; }

	Vector3		GetForward() override;
};

#endif // CAMERA_H