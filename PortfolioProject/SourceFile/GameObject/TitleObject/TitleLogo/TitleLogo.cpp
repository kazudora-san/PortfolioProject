#include	"Main.h"
#include	"TitleLogo.h"
#include	"Renderer/Renderer.h"
#include	"Texture/Texture.h"

void TitleLogo::Init(float x, float y, float Width, float Height, const char* FileName)
{
	// 頂点バッファの情報を作る
	// 今回は四角形なので４つの頂点情報を入力する必要がある！
	VERTEX_3D vertex[4] = {};

	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(Width, 0.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f, Height, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(Width, Height, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	m_Position = { x, y - 200.0f, 0.0f };
	m_EndPosition = { x, y, 0.0f };
	m_BaseScale = m_Scale;

	m_Spring = 0.15f;
	m_Damping = 0.85f;

	m_Texture = Texture::Load(FileName);

	Renderer::CreateVertexShader(
		&m_VertexShader,
		&m_VertexLayOut,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(
		&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");
}

void TitleLogo::Uninit()
{
	m_VertexBuffer->Release();
	m_VertexLayOut->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TitleLogo::Update()
{
	// ===== ばね移動 =====
	Vector3 diff = {};

	diff.x = m_EndPosition.x - m_Position.x;
	diff.y = m_EndPosition.y - m_Position.y;

	m_Velocity.x += diff.x * m_Spring;
	m_Velocity.y += diff.y * m_Spring;

	m_Velocity.x *= m_Damping;
	m_Velocity.y *= m_Damping;

	m_Position.x += m_Velocity.x;
	m_Position.y += m_Velocity.y;

	// ===== スクワッシュ＆ストレッチ =====
	float vy = m_Velocity.y;

	if (vy < -0.05f)
	{
		// 落下中 → 縦に伸びる
		m_Scale.y = m_BaseScale.y * (1.0f + m_SquashPower);
		m_Scale.x = m_BaseScale.x * (1.0f - m_SquashPower);
	}
	else if (vy > 0.05f)
	{
		// 上昇中 → 横に伸びる
		m_Scale.x = m_BaseScale.x * (1.0f + m_SquashPower);
		m_Scale.y = m_BaseScale.y * (1.0f - m_SquashPower);
	}
	else
	{
		// 停止時 → 元に戻す（補間）
		m_Scale.x += (m_BaseScale.x - m_Scale.x) * 0.2f;
		m_Scale.y += (m_BaseScale.y - m_Scale.y) * 0.2f;
	}

	// 完全停止したら固定
	if (fabsf(m_Velocity.y) < 0.01f)
	{
		m_Position = m_EndPosition;
		m_Scale = m_BaseScale;
		m_Velocity = { 0.0f, 0.0f, 0.0f };
	}
}

void TitleLogo::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	XMMATRIX world = {};
	XMMATRIX scale = {};
	XMMATRIX rot = {};
	XMMATRIX trans = {};

	scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	rot = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, 0.0f);
	trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	world = scale * rot * trans;

	Renderer::SetWorldMatrix(world);

	// マテリアル設定
	MATERIAL material = {};
	material.Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
	material.TextureEnable = true;

	Renderer::SetMaterial(material);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	Renderer::GetDeviceContext()->IASetVertexBuffers(
		0,
		1,
		&m_VertexBuffer,
		&stride,
		&offset);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);
}