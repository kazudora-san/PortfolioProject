#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Enemy/Enemy.h"
#include	"Camera/Camera.h"
#include	"Renderer/Renderer.h"
#include	"ModelRenderer/ModelRenderer.h"
#include	"Scene/Scene.h"
#include	"Input/Input.h"

void Enemy::Init()
{
	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->Load("asset\\model\\player.obj");

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

}

void Enemy::Uninit()
{
	delete m_ModelRenderer;

	m_VertexLayOut->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Enemy::Update()
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

void Enemy::Draw()
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
