#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"Grassinstance.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Field/MeshField/MeshField.h"
#include	"Camera/Camera.h"
#include	"Texture/Texture.h"
#include	"Scene/Scene.h"

void GrassInstance::Init()
{
	VERTEX_3D vertex[4];
	vertex[0].Position = XMFLOAT3(-0.5f, 1.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(0.5f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, 0.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5f, 0.0f, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読込
	m_Texture = Texture::Load("Asset\\Texture\\Grass.png");

	{//ストラクチャードバッファ生成
		m_InstanceNum = 100000;

		Vector3* position = new Vector3[m_InstanceNum]{};
		MeshField* field = SceneManager::GetScene()->GetGameObject<MeshField>();
		if (!field)
		{
			return;
		}

		for (unsigned int i = 0; i < m_InstanceNum; i++)
		{
			position[i].x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
			position[i].z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
			position[i].y = field->GetHeight(position[i]);
		}

		D3D11_BUFFER_DESC bd{};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(Vector3) * m_InstanceNum;
		bd.StructureByteStride = sizeof(Vector3);
		bd.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		bd.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = position;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_PositionBuffer);

		delete[] position;

		//シェーダーリソースビュー生成
		D3D11_SHADER_RESOURCE_VIEW_DESC srvd{};
		srvd.Format = DXGI_FORMAT_UNKNOWN;
		srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		srvd.Buffer.FirstElement = 0;
		srvd.Buffer.NumElements = m_InstanceNum;

		Renderer::GetDevice()->CreateShaderResourceView(m_PositionBuffer,
			&srvd, &m_PositionSRV);
	}

	//シェーダー読込
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\grassVS.cso");


	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\grassPS.cso");
}

void GrassInstance::Uninit()
{
	//m_Texture->Release();
	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
	m_PositionBuffer->Release();
	m_PositionSRV->Release();
}

void GrassInstance::Update()
{
}

void GrassInstance::Draw()
{
	Camera* camera = SceneManager::GetScene()->GetGameObject<Camera>();
	if (!camera)
	{
		return;
	}
	//視錐台カリング
	//if (camera->CheckView(m_Position/*, 0.5f * m_Scale.x*/) == false)
	//	return;

	//距離カリング
	Vector3 cameraPos = camera->GetPosition();
	float length = (m_Position - cameraPos).length();

	//if (length > 20.0f)
	//	return;

	//float alpha = (20.0f - length) / 20.0f;

	float alpha = 1.0f;

	//入カレイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX view = camera->GetViewMatrix();

	//ビューの逆行列
	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view);//1T5
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	XMMATRIX world, scale, trans;
	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	//rot = XMMatrixRotat ionRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	world = scale * invView * trans;
	Renderer::SetWorldMatrix(world);

	//// マテリアル設定
	//MATERIAL material{};
	//material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	//material.TextureEnable = true;
	//Renderer:: SetMaterial(material);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//ストラクチャードバッファ
	Renderer::GetDeviceContext()->VSSetShaderResources(2, 1, &m_PositionSRV);

	// ブリミティブトボロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ボリゴン描画
	Renderer::GetDeviceContext()->DrawInstanced(4, m_InstanceNum, 0, 0);
}
