#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Rock/Rock.h"
#include	"Camera/Camera.h"
#include	"Renderer/Renderer.h"
#include	"ModelRenderer/ModelRenderer.h"
#include	"Scene/Scene.h"
#include	"Input/Input.h"

void Rock::Init()
{
	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->Load("asset\\model\\rock.obj");

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

}

void Rock::Uninit()
{
	delete m_ModelRenderer;

	m_VertexLayOut->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Rock::Update()
{
}

void Rock::Draw()
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
