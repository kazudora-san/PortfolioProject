#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Bullet/Bullet.h"
#include	"Camera/Camera.h"
#include	"Renderer/Renderer.h"
#include	"ModelRenderer/ModelRenderer.h"
#include	"Input/Input.h"
#include	"Player/Player.h"
#include	"Enemy/Enemy.h"
#include	"Effect/Explosion/Explosion.h"
#include	"Effect/Heart/Heart.h"
#include	"Scene/Scene.h"
#include	"Score/Score.h"
#include	"Manager/AudioManager/AudioManager.h"


void Bullet::Init()
{
	m_ModelRenderer = new ModelRenderer();
	m_ModelRenderer->Load("asset\\model\\bullet.obj");

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Audio->Init();
	m_Audio->Load("asset\\audio\\EnemyDestroy.wav", "EnemyDestroy");
}

void Bullet::Uninit()
{
	delete m_ModelRenderer;

	m_VertexLayOut->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Bullet::Update()
{
	m_Position += m_Velocity;
	auto player = SceneManager::GetScene()->GetGameObject<Player>();
	
	Vector3 rot = player->GetRotation(); // ← プレイヤーの回転（単位はラジアン）

	Vector3 direction;
	direction.x = sinf(rot.y);  // Y軸回転で左右の方向を決める
	direction.y = 0.0f;         // 水平射出ならY方向は0
	direction.z = cosf(rot.y);  // 前後の方向

	//m_Time += 0.01f;
	//float i = m_Time;

	//m_Position = m_StartPosition * (2.0f * i * i * i - 3.0f * i * i + 1.0f)
	//	+ m_EndPosition * (-2.0f * i * i * i + 3.0f * i * i)
	//	+ m_StartVector * (i * i * i - 2.0f * i * i + i)
	//	+ m_EndVector * (i * i * i - i * i);

	auto particleS = SceneManager::GetScene()->AddGameObject<Explosion>(1);
	particleS->SetPosition(m_Position + Vector3(0.0f, 0.0f, 0.0f));

	if (m_Position.length() > 20.0f)
	{
		SetDestroy();
	}

	
	//衝突判定
	auto enemies = SceneManager::GetScene()->GetGameObjects<Enemy>();
	bool particle = false;

	// 当たり判定処理
	for (auto enemy : enemies)
	{
		Vector3 d = enemy->GetPosition() - m_Position;
		float length = d.length();
		if (length < 1.0f && !particle)
		{
			SceneManager::GetScene()->AddGameObject<Explosion>(1)->
				SetPosition(enemy->GetPosition() + Vector3(0.0f,1.0f,0.0f));

			Heart* particle = SceneManager::GetScene()->AddGameObject<Heart>(1);
			particle->SetPosition(enemy->GetPosition());

			enemy->SetDestroy();
			SetDestroy();
			m_Audio->Play("EnemyDestroy");

			Score* score = SceneManager::GetScene()->GetGameObject<Score>();
			score->AddScore(100);
		}
	}
}

void Bullet::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);




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

void Bullet::SetVelocity(Vector3 v)
{
	m_Velocity = v;
}

void Bullet::Shot(Vector3 StartPosition, Vector3 EndPosition)
{
	m_StartPosition = StartPosition;
	m_EndPosition = EndPosition;
	m_StartVector = Vector3(2.0f, 100.0f, 0.0f);
	m_EndVector = Vector3(10.0f, -10.0f, 0.0f);
	m_Time = 0.0f;
}