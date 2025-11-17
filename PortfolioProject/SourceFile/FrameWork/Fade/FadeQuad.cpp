#include	"Main.h"
#include	"Render/Renderer.h"
#include	"Fade/FadeQuad.h"
#include	"Texture/Texture.h"
#include	"Render/Polygon2D.h"
#include	<algorithm>
#include	<cmath>

void FadeQuad::drawFullScreen(float alpha, const XMFLOAT3& rgb)
{
	if (!m_VertexBuffer || !m_TexWhite)
	{
		return;
	}

	auto* dc = Renderer::GetDeviceContext();
	dc->IASetInputLayout(m_VertexLayout);
	dc->VSSetShader(m_VertexShader, nullptr, 0);
	dc->PSSetShader(m_PixelShader, nullptr, 0);

	Renderer::SetWorldViewProjection2D();

	MATERIAL mat{};
	mat.Diffuse = XMFLOAT4(rgb.x, rgb.y, rgb.z, alpha);
	mat.TextureEnable = true;
	Renderer::SetMaterial(mat);

	UINT stride = sizeof(VERTEX_3D), offset = 0;
	dc->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	dc->PSSetShaderResources(0, 1, &m_TexWhite);

	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	dc->Draw(4, 0);
}

float FadeQuad::easeInOutSine(float x) 
{
	return -0.5f * (cosf(3.14159265f * x) - 1.0f);
}

void FadeQuad::Init()
{
	// 頂点作成
	VERTEX_3D vertex[4]{};
	vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Position = XMFLOAT3((float)SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[2].Position = XMFLOAT3(0.0f, (float)SCREEN_HEIGHT, 0.0f);
	vertex[3].Position = XMFLOAT3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f);

	for (int i = 0; i < 4; i++) 
	{
		vertex[i].Normal = XMFLOAT3(0, 0, 0);
		vertex[i].Diffuse = XMFLOAT4(1, 1, 1, 1);
	}
	vertex[0].TexCoord = XMFLOAT2(0, 0);
	vertex[1].TexCoord = XMFLOAT2(1, 0);
	vertex[2].TexCoord = XMFLOAT2(0, 1);
	vertex[3].TexCoord = XMFLOAT2(1, 1);

	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA srd{};
	srd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &srd, &m_VertexBuffer);

	// シェーダ
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\unlitTexturePS.cso");

	// 白1×1テクスチャを読み込む
	m_TexWhite = Texture::Load("asset\\texture\\white.png");
}

void FadeQuad::Uninit()
{
	m_TexWhite = nullptr;
	if (m_VertexBuffer) 
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = nullptr;
	}
	if (m_VertexLayout)
	{
		m_VertexLayout->Release();
		m_VertexLayout = nullptr;
	}
	if (m_VertexShader)
	{
		m_VertexShader->Release();
		m_VertexShader = nullptr;
	}
	if (m_PixelShader)
	{
		m_PixelShader->Release();
		m_PixelShader = nullptr;
	}
}

void FadeQuad::FadeIn(float duration, XMFLOAT3 color, std::function<void()> onDone)
{
	m_Mode = FadeMode::In;
	m_t = 0.0f;
	m_dur = (std::max)(0.0001f, duration);
	m_color = color;
	m_alpha = 1.0f;
	m_onDone = std::move(onDone);
}

void FadeQuad::FadeOut(float duration, XMFLOAT3 color, std::function<void()> onDone)
{
	m_Mode = FadeMode::Out;
	m_t = 0.0f;
	m_dur = (std::max)(0.0001f, duration);
	m_color = color;
	m_alpha = 0.0f;
	m_onDone = std::move(onDone);
}

void FadeQuad::Update()
{
	if (m_Mode == FadeMode::None) return;

	m_t += 1.0f / 60.0f;
	float u = (std::min)(m_t / m_dur, 1.0f);
	float e = easeInOutSine(u);

	if (m_Mode == FadeMode::In) m_alpha = 1.0f - e;
	if (m_Mode == FadeMode::Out) m_alpha = e;

	if (u >= 1.0f) {
		auto cb = m_onDone; m_Mode = FadeMode::None;
		if (cb) cb();
	}
}

void FadeQuad::Draw()
{
	if (m_Mode == FadeMode::None || m_alpha <= 0.0f) return;
	drawFullScreen(m_alpha, m_color);
}