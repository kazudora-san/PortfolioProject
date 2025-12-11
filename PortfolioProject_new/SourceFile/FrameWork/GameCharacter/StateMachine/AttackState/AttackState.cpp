#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"AttackState.h"
#include	"Manager/AudioManager/AudioManager.h"
#include	"Camera/Camera.h"
#include	"Renderer/Renderer.h"
#include	"Renderer/ModelRenderer/ModelRenderer.h"
#include	"Input/Input.h"
#include	"Bullet/Bullet.h"
#include	"Enemy/Enemy.h"
#include	"Scene/Scene.h"
#include	"AnimationModel/AnimationModel.h"
#include	"Field/MeshField/MeshField.h"
#include	"Effect/Explosion/Explosion.h"
#include	"Score/Score.h"
#include	"Effect/Heart/Heart.h"

void AttackState::Init()
{
	m_Frame = 0;

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");
}

void AttackState::Uninit()
{

}

void AttackState::Update()
{
}

void AttackState::Draw()
{
	
}

bool AttackState::IsActive() const
{
	
	return false;
}
