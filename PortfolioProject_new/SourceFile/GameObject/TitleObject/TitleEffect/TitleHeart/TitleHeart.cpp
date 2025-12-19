#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"TitleEffect/TitleHeart/TitleHeart.h"
#include	"Input/Input.h"
#include	"TitleCamera/TitleCamera.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Scene/Scene.h"
#include	"Texture/Texture.h"


Vector3 TitleHSVtoRGB(float h, float s, float v);

void TitleHeart::Init()
{
	// 頂点バッファの情報を作る
	// 今回は四角形なので４つの頂点情報を入力する必要がある！
	VERTEX_3D vertex[4];

	vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
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

	m_Texture = Texture::Load("Asset\\Texture\\Particle.png");

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");

	for (int i = 0; i < TitleHeartMax; i++)
	{
		m_TitleHeartStart[i].Enable = false;
		m_TitleHeartEnd[i].Enable = false;
	}

	// ベジェ曲線参考リンク
	// ====================================================
	// https://www.desmos.com/calculator/uzjjw5ouzt?lang=ja
	// ====================================================
	
	


	m_Scale = Vector3(0.2f, 0.2f, 0.2f);
}

void TitleHeart::Uninit()
{
	//m_Texture->Release();

	m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TitleHeart::Update()
{
	// ハートの右側のポジション
	m_StartLine[0] = Vector3(GetPosition().x, GetPosition().y, GetPosition().z);
	m_StartLine[1] = m_StartLine[0] + Vector3(0.0f, 2.0f, 0.0f);
	m_StartLine[2] = m_StartLine[0] + Vector3(2.5f, 1.0f, 0.0f);
	m_StartLine[3] = m_StartLine[0] + Vector3(0.0f, -1.0f, 0.0f);

	// ハートの左側のポジション
	m_EndLine[0] = Vector3(GetPosition().x, GetPosition().y, GetPosition().z);
	m_EndLine[1] = m_EndLine[0] + Vector3(0.0f, 2.0f, 0.0f);
	m_EndLine[2] = m_EndLine[0] + Vector3(-2.5f, 1.0f, 0.0f);
	m_EndLine[3] = m_EndLine[0] + Vector3(0.0f, -1.0f, 0.0f);

	m_Time += 0.01f;

	float i = m_Time;
	
	// ベジェ曲線の計算
	// 右側
	m_StartPosition = (1.0f - i) * (1.0f - i) * (1.0f - i) * m_StartLine[0] +
		3.0f * (1.0f - i) * (1.0f - i) * i * m_StartLine[1] +
		3.0f * (1.0f - i) * i * i * m_StartLine[2] +
		i * i * i * m_StartLine[3];

	// 左側
	m_EndPosition = (1.0f - i) * (1.0f - i) * (1.0f - i) * m_EndLine[0] +
		3.0f * (1.0f - i) * (1.0f - i) * i * m_EndLine[1] +
		3.0f * (1.0f - i) * i * i * m_EndLine[2] +
		i * i * i * m_EndLine[3];

	int cnt = 10;

	// 使われていない場所を探す
	// 同じ個数なので、まとめて処理してる
	for (int i = 0; i < TitleHeartMax; i++)
	{
		// 使われていないところを探す
		if (m_TitleHeartStart[i].Enable == false)
		{
			// 初期値をセット
			m_TitleHeartStart[i].Enable = true;
			m_TitleHeartStart[i].Life = 120;
			m_TitleHeartStart[i].Position = m_StartPosition;
			cnt--;
		}

		if (m_TitleHeartEnd[i].Enable == false)
		{
			m_TitleHeartEnd[i].Enable = true;
			m_TitleHeartEnd[i].Life = 120;
			m_TitleHeartEnd[i].Position = m_EndPosition;
			cnt--;
			break;
		}
	}

	// パーティクルの移動
	for (int i = 0; i < TitleHeartMax; i++)
	{
		if (m_TitleHeartStart[i].Enable == true)
		{
			// ライフを引く
			m_TitleHeartStart[i].Life--;

			// ライフが０になったら消す
			if (m_TitleHeartStart[i].Life <= 0)
			{
				m_TitleHeartStart[i].Enable = false;
			}
		}

		if (m_TitleHeartEnd[i].Enable == true)
		{
			// ライフを引く
			m_TitleHeartEnd[i].Life--;

			// ライフが０になったら消す
			if (m_TitleHeartEnd[i].Life <= 0)
			{
				m_TitleHeartEnd[i].Enable = false;
			}
		}
	}

	if (m_Time > 2.5f)
	{
		m_Time = 0.0f;
		//SetDestroy();
	}
}

void TitleHeart::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	TitleCamera* titleCamera = SceneManager::GetScene()->GetGameObject<TitleCamera>();

	XMMATRIX view = titleCamera->GetViewMatrix();

	// ビューの逆行列
	XMMATRIX invView;
	invView = XMMatrixInverse(nullptr, view); // 逆行列
	invView.r[3].m128_f32[0] = 0.0f;
	invView.r[3].m128_f32[1] = 0.0f;
	invView.r[3].m128_f32[2] = 0.0f;

	

	// 奥行処理をOFF
	Renderer::SetDepthEnable(false);
	Renderer::SetAddEnable(true);

	// パーティクルの描画
	for (int i = 0; i < TitleHeartMax; i++)
	{
		// 虹色にする
		// 左の値を大きくしすぎると、値が少ししか変わらなくて
		// グラデーションに見えなくなる！
		float hue = fmodf(static_cast<float>(i % 100) / 100.0f, 1.0f);
		Vector3 rgb = TitleHSVtoRGB(hue, 1.0f, 1.0f);

		// マテリアル設定
		MATERIAL material{};
		material.Diffuse = { rgb.x, rgb.y, rgb.z, 1.0f };
		material.TextureEnable = true;
		Renderer::SetMaterial(material);

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		// VertexBufferで生成した情報を使って下さいという意味
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		// テクスチャ設定
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

		// ブリミティブトボロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		float offset_y = 2.0f;

		if (m_TitleHeartStart[i].Enable == true)
		{
			// 3Dマトリクス設定
			XMMATRIX world, scale, trans;
			scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
			trans = XMMatrixTranslation(m_TitleHeartStart[i].Position.x,
										m_TitleHeartStart[i].Position.y + offset_y,
										m_TitleHeartStart[i].Position.z);
			world = scale * invView * trans;
			Renderer::SetWorldMatrix(world);

			// ボリゴン描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}

		if (m_TitleHeartEnd[i].Enable == true)
		{
			// 3Dマトリクス設定
			XMMATRIX world, scale, trans;
			scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
			trans = XMMatrixTranslation(m_TitleHeartEnd[i].Position.x,
										m_TitleHeartEnd[i].Position.y + offset_y,
										m_TitleHeartEnd[i].Position.z);
			world = scale * invView * trans;
			Renderer::SetWorldMatrix(world);

			// ボリゴン描画
			Renderer::GetDeviceContext()->Draw(4, 0);
		}
	}
	Renderer::SetAddEnable(false);
	// 奥行処理をON
	Renderer::SetDepthEnable(true);
}

Vector3 TitleHSVtoRGB(float h, float s, float v)
{
	float r, g, b;

	int i = static_cast<int>(h * 6);
	float f = h * 6 - i;
	float p = v * (1 - s);
	float q = v * (1 - f * s);
	float t = v * (1 - (1 - f) * s);

	switch (i % 6)
	{
	case 0: r = v; g = t; b = p;
		break;
	case 1: r = q; g = v; b = p; 
		break;
	case 2: r = p; g = v; b = t; 
		break;
	case 3: r = p; g = q; b = v; 
		break;
	case 4: r = t; g = p; b = v; 
		break;
	case 5: r = v; g = p; b = q; 
		break;
	}

	return Vector3(r, g, b);
}
