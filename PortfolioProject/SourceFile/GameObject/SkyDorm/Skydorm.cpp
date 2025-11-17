#include	"Main.h"
#include	"Render/Renderer.h"
#include	"Render/ModelRenderer.h"
#include	"Skydorm/Skydorm.h"
#include	"Input/Input.h"
#include	"Camera/Camera.h"
#include	"Scene/Scene.h"
#include	"Manager/SceneManager/SceneManager.h"

void SkyDorm::Init()
{
	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->Load("asset\\model\\sky.obj");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	// 基本は拡大する
	m_Scale = { 200.0f, 200.0f, 200.0f };
}

void SkyDorm::Uninit()
{
	delete m_ModelRenderer;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void SkyDorm::Update()
{
	Camera* camera = SceneManager::GetScene()->GetGameObject<Camera>();

	m_Position = camera->GetPosition();
}

void SkyDorm::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// 3Dマトリクス設定
	XMMATRIX world, scale, rot, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + XM_PI, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(world);

	m_ModelRenderer->Draw();
}
