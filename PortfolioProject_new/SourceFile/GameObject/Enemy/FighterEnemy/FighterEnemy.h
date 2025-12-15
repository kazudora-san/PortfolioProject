#ifndef		FIGHTERENEMY_H
#define		FIGHTERENEMY_H

#include	"GameCharacter/EnemyBase/EnemyBase.h"

class FighterEnemy :public EnemyBase
{
private:

	ID3D11InputLayout*		m_VertexLayOut	= {};
	ID3D11PixelShader*		m_PixelShader	= {};
	ID3D11VertexShader*		m_VertexShader	= {};


	class ModelRenderer*	m_ModelRenderer	= {};

	unsigned int			m_Frame			= {};

public:
	virtual void	Init()		override;
	virtual void	Uninit()	override;
	virtual void	Update()	override;
	virtual void	Draw()		override;

};

#endif