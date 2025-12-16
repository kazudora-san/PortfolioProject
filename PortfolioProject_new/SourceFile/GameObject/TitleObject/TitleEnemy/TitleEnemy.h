#ifndef		TITLEENEMY_H
#define		TITLEENEMY_H

#include	"GameObject.h"

class AnimationModel;

class TitleEnemy :public GameObject
{
private:

	ID3D11InputLayout*		m_VertexLayOut		= {};
	ID3D11PixelShader*		m_PixelShader		= {};
	ID3D11VertexShader*		m_VertexShader		= {};


	AnimationModel*			m_AnimationModel	= {};

	unsigned int			m_Frame				= {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

};

#endif