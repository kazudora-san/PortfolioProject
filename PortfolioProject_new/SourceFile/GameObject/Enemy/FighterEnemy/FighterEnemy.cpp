#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"FighterEnemy.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Camera/Camera.h"
#include	"Renderer/ModelRenderer/ModelRenderer.h"
#include	"Scene/Scene.h"

void FighterEnemy::Init()
{
	EnemyBase::Init();

	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->Load("Asset\\model\\Player.obj");

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");

}

void FighterEnemy::Uninit()
{
	delete m_ModelRenderer;

	EnemyBase::Uninit();
}

void FighterEnemy::Update()
{
	Camera* camera = SceneManager::GetScene()->GetGameObject<Camera>();

	Vector3 rotation = camera->GetRotation();

	if (m_Frame > 60)
	{
		m_Position += GetRight() * 0.01f;
	}
	else
	{
		m_Position -= GetRight() * 0.01f;
	}

	m_Rotation.y = rotation.y;

	if (m_Frame > 120)
	{
		m_Frame = 0;
	}
	else
	{
		m_Frame++;
	}
}

void FighterEnemy::Draw()
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


	m_ModelRenderer->Draw();
}
