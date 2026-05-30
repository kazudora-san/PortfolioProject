#include "Main.h"
#include "Renderer/Renderer.h"
#include "TitlePlayer.h"
#include "Renderer/ModelRenderer/ModelRenderer.h"
#include "Manager/SceneManager/SceneManager.h"
#include "Manager/AudioManager/AudioManager.h"
#include "Camera/Camera.h"
#include "Input/Input.h"
#include "Bullet/Bullet.h"
#include "Enemy/FighterEnemy/FighterEnemy.h"
#include "Scene/Scene.h"
#include "AnimationModel/AnimationModel.h"
#include "Field/MeshField/MeshField.h"
#include "Effect/Explosion/Explosion.h"
#include "Score/Score.h"
#include "Effect/Heart/Heart.h"

void TitlePlayer::Init()
{
	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");

	m_Rotation.y = -90.0f;

	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("Asset\\model\\OtamesiModel.fbx");

	m_AnimationModel->LoadAnimation("Asset\\model\\OtamesiIdle.fbx", "Idle");

	m_AnimationName = "Idle";
	m_AnimationNameNext = "Idle";
	m_AnimationBlend = 0.0f;
}

void TitlePlayer::Uninit()
{}

void TitlePlayer::Update()
{
	m_AnimationModel->Update(m_AnimationName.c_str(), m_Frame,
		m_AnimationNameNext.c_str(), m_Frame,
		m_AnimationBlend);
	m_Frame++;

	m_AnimationBlend += 0.15f;
	if (m_AnimationBlend > 1.0f)
	{
		// 線形補間
		m_AnimationBlend = 1.0f;
	}
}

void TitlePlayer::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//親
	{
		//マトリクス設定
		XMMATRIX world, scale, rot, trans;
		scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		world = scale * rot * trans;

		Renderer::SetWorldMatrix(world);

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		material.TextureEnable = true;
		Renderer::SetMaterial(material);

		m_AnimationModel->Draw();
	}
}