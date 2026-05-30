#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"TitleEnemy.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Camera/Camera.h"
#include	"AnimationModel/AnimationModel.h"
#include	"Scene/Scene.h"

void TitleEnemy::Init()
{
	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("Asset\\model\\Enemy_Model.fbx");
	m_AnimationModel->LoadAnimation("Asset\\model\\Enemy_Idle.fbx", "EnemyIdle");

	if (m_AnimationNameNext != "EnemyIdle")
	{
		// Idle以外が入ってれば、Idleのアニメーションを入れて、Blendを0.0fにする
		m_AnimationName = "EnemyIdle";
		m_AnimationNameNext = "EnemyIdle";
		m_AnimationBlend = 0.0f;
	}

	// シェーダー読み込み
	Renderer::CreateVertexShader(
		&m_VertexShader,
		&m_VertexLayOut,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(
		&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");

	m_Scale = { 0.01f, 0.01f, 0.01f };
}

void TitleEnemy::Uninit()
{
	delete m_AnimationModel;
}

void TitleEnemy::Update()
{
	// std::string型には、c_str()というconst char*型に変換してくれる！
	// 二つ入れることで、合成（ブレンド）をしてくれる！（処理は中身を参照）
	m_AnimationModel->Update(
		m_AnimationName.c_str(),
		m_Frame,
		m_AnimationNameNext.c_str(),
		m_Frame,
		m_AnimationBlend);

	m_Frame++;

	m_AnimationBlend += 0.007f;

	if (m_AnimationBlend > 1.0f)
	{
		// 線形補間
		m_AnimationBlend = 1.0f;
	}
}

void TitleEnemy::Draw()
{
	// 入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);

	// マトリクス設定
	XMMATRIX world = {};
	XMMATRIX scale = {};
	XMMATRIX rot = {};
	XMMATRIX trans = {};

	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(
		m_Rotation.x,
		m_Rotation.y,
		m_Rotation.z);

	trans = XMMatrixTranslation(
		m_Position.x,
		m_Position.y,
		m_Position.z);

	world = scale * rot * trans;

	Renderer::SetWorldMatrix(world);

	// マテリアル設定
	MATERIAL material = {};
	material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.TextureEnable = true;

	Renderer::SetMaterial(material);

	m_AnimationModel->Draw();
}