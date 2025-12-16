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
	m_AnimationModel->Load("Asset\\model\\Player.obj");

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");
}

void TitleEnemy::Uninit()
{
	delete m_AnimationModel;
}

void TitleEnemy::Update()
{
}

void TitleEnemy::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//マトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	//マテリアル設定
	MATERIAL material{};
	material.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	material.TextureEnable = true;
	Renderer::SetMaterial(material);


	m_AnimationModel->Draw();
}
