#ifndef		BULLET_H
#define		BULLET_H

#include	"GameObject.h"

class AudioManager;
class ModelRenderer;

class Bullet : public GameObject
{
private:

	ID3D11InputLayout*		m_VertexLayOut	= {};
	ID3D11PixelShader*		m_PixelShader	= {};
	ID3D11VertexShader*		m_VertexShader	= {};


	ModelRenderer*			m_ModelRenderer = {};

	Vector3					m_Velocity		= {};

	Vector3					m_StartPosition	= {};
	Vector3					m_EndPosition	= {};
	Vector3					m_StartVector	= {};
	Vector3					m_EndVector		= {};

	float					m_Time			= {};

	AudioManager*			m_Audio			= {};
public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

	void	SetVelocity	(Vector3 v);
	void	Shot		(Vector3 StartPosition, Vector3 EndPosition);
};

#endif // BULLET_H