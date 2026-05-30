#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"PlayerModel.h"
#include	"Camera/Camera.h"
#include	"Renderer/Renderer.h"
#include	"Renderer/ModelRenderer/ModelRenderer.h"
#include	"Input/Input.h"
#include	"Scene/Scene.h"
#include	"AnimationModel/AnimationModel.h"

void PlayerModel::Init()
{
	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("Asset\\model\\OtamesiModel.fbx");

	m_AnimationModel->LoadAnimation("Asset\\model\\OtamesiRun.fbx", "Run");
	m_AnimationModel->LoadAnimation("Asset\\model\\OtamesiIdle.fbx", "Idle");

	m_AnimationName = "Idle";
	m_AnimationNameNext = "Idle";
	m_AnimationBlend = 0.0f;
	m_Frame = 0;

	// シェーダー読み込み
	Renderer::CreateVertexShader(
		&m_VertexShader,
		&m_VertexLayOut,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(
		&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");
}

void PlayerModel::Uninit()
{
	m_AnimationModel->Uninit();
	delete m_AnimationModel;

	m_VertexLayOut->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void PlayerModel::Update()
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

	m_AnimationBlend += 0.15f;

	if (m_AnimationBlend > 1.0f)
	{
		// 線形補間
		m_AnimationBlend = 1.0f;
	}
}

void PlayerModel::Draw()
{
	// 入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	// シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX world = {};
	XMMATRIX scale = {};
	XMMATRIX rot = {};
	XMMATRIX trans = {};

	scale = XMMatrixScaling(
		m_Scale.x,
		m_Scale.y,
		m_Scale.z);

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