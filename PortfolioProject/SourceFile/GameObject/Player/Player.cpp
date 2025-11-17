#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Player/Player.h"
#include	"Camera/Camera.h"
#include	"Render/Renderer.h"
#include	"Render/ModelRenderer.h"
#include	"Input/Input.h"
#include	"Bullet/Bullet.h"
#include	"Enemy/Enemy.h"
#include	"Scene/Scene.h"
#include	"AnimationModel/AnimationModel.h"
#include	"Field/MeshField/MeshField.h"
#include	"Effect/Explosion/Explosion.h"
#include	"Score/Score.h"
#include	"Effect/Heart/Heart.h"
#include	"Audio/Audio.h"


void Player::Init()
{
	//m_ModelRenderer = new ModelRenderer();
	//m_ModelRenderer->Load("asset\\model\\player.obj");

	//m_ModelRendererChild = new ModelRenderer();
	//m_ModelRendererChild->Load("asset\\model\\player.obj");
	

	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("asset\\model\\otamesi_model.fbx");

	m_AnimationModel->LoadAnimation("asset\\model\\otamesi_Run.fbx", "Run");
	m_AnimationModel->LoadAnimation("asset\\model\\otamesi_Idle.fbx", "Idle");

	m_AnimationName = "Idle";
	m_AnimationNameNext = "Idle";
	m_AnimationBlend = 0.0f;
	m_Frame = 0;

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	
	m_Audio->Init();
	m_Audio->Load("asset\\audio\\GameBGM.wav", "GameBGM");
	//m_Audio->Play("GameBGM", true);
	m_Audio->Load("asset\\audio\\Shot.wav", "ShotSE");
	m_Audio->Load("asset\\audio\\Run.wav", "RunSE");
}

void Player::Uninit()
{
	//delete m_ModelRenderer;
	//delete m_ModelRendererChild;
	m_Audio->Uninit();

	m_AnimationModel->Uninit();
	delete m_AnimationModel;

	m_VertexLayOut->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void Player::Update()
{
	Camera* camera = SceneManager::GetScene()->GetGameObject<Camera>();

	Vector3 rotation = camera->GetRotation();

	bool move = false;

	if (Input::GetKeyPress('A'))
	{
		m_Position += camera->GetRight() * -0.1f;
		m_Rotation.y = rotation.y - XM_PIDIV2;
		move = true;
	}
	if (Input::GetKeyPress('D'))
	{
		m_Position += camera->GetRight() * 0.1f;
		m_Rotation.y = rotation.y + XM_PIDIV2;
		move = true;
	}
	if (Input::GetKeyPress('W'))
	{
		Vector3 forward = camera->GetForward();
		forward.y = 0.0f;
		forward.normalize();
		m_Position += forward * 0.1f;
		m_Rotation.y = rotation.y;
		move = true;
	}
	if (Input::GetKeyPress('S'))
	{
		Vector3 forward = camera->GetForward();
		forward.y = 0.0f;
		forward.normalize();

		m_Position += forward * -0.1f;
		m_Rotation.y = rotation.y + XM_PI;
		move = true;
	}


	MeshField* meshField = SceneManager::GetScene()->GetGameObject<MeshField>();
	float groundY = meshField->GetHeight(m_Position);

	// ジャンプ処理
	if (Input::GetKeyTrigger('F') && !m_IsJump)
	{
		m_JumpTime = 0.0f;
		m_IsJump = true;
	}

	// ジャンプ中
	if (m_IsJump)
	{
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
				SceneManager::GetScene()->AddGameObject<Exprosion>(1)->
					SetPosition(enemy->GetPosition() + Vector3(0.0f, 1.0f, 0.0f));

				Heart* particle = SceneManager::GetScene()->AddGameObject<Heart>(1);
				particle->SetPosition(enemy->GetPosition());

				enemy->SetDestroy();

				Score* score = SceneManager::GetScene()->GetGameObject<Score>();
				score->AddScore(1);
			}
		}

		m_JumpTime += 0.016f;          // 1フレーム時間
		float t = m_JumpTime / 2.0f;   // 2秒間でジャンプ
		if (t > 1.0f)
		{
			t = 1.0f;
		}

		// 放物線で高さ計算
		float jumpHeight = 3.0f * 4.0f * t * (1.0f - t);

		// 地形の高さを基準にする
		m_Position.y = groundY + jumpHeight;

		// 地面に到達したら止める
		if (m_Position.y <= groundY)
		{
			m_Position.y = groundY;
			m_IsJump = false;
		}
	}
	else
	{
		// 通常時は地形に沿う
		m_Position.y = groundY;
	} 


	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Bullet* bullet = SceneManager::GetScene()->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position);
		bullet->SetVelocity(GetForward() * 0.5f);
		//m_Audio->Play("ShotSE", false);
		//Enemy* enemy = Manager::GetGameObject<Enemy>();
		//bullet->Shot(m_Position, enemy->GetPosition());
	}

	if (move)
	{
		// プレイヤーが動くとき、Runのアニメーションか？
		if (m_AnimationNameNext != "Run")
		{
			// Run以外が入ってれば、Runのアニメーションを入れて、Blendを0.0fにする
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = "Run";
			m_AnimationBlend = 0.0f;
			//m_Audio->Play("RunSE", true);
		}
	}
	else
	{
		// プレイヤーが止まる時、Idleのアニメーションか？
		if (m_AnimationNameNext != "Idle")
		{
			// Idle以外が入ってれば、Idleのアニメーションを入れて、Blendを0.0fにする
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = "Idle";
			m_AnimationBlend = 0.0f;
			m_Audio->Stop("RunSE");
		}
	}
	
	// std::string型には、c_str()というconst char*型に変換してくれる！
	// 二つ入れることで、合成（ブレンド）をしてくれる！（処理は中身を参照）
	m_AnimationModel->Update(m_AnimationName.c_str(), m_Frame,
								m_AnimationNameNext.c_str(), m_Frame,
								m_AnimationBlend);
	m_Frame++;

	m_AnimationBlend += 0.15f;
	if (m_AnimationBlend > 1.0f)
	{
		// 線形補間
		m_AnimationBlend = 1.0f;
	}
}

void Player::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//XMMATRIX parentMatrix;

	//親
	{
		//マトリクス設定
		XMMATRIX world, scale, rot, trans;
		scale = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		rot = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		trans = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
		world = scale * rot * trans;

		//parentMatrix = world;
		Renderer::SetWorldMatrix(world);

		//マテリアル設定
		MATERIAL material{};
		material.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
		material.TextureEnable = true;
		Renderer::SetMaterial(material);


		//m_ModelRenderer->Draw();

		m_AnimationModel->Draw();
	}

	////子
	//{
	//	//マトリクス設定
	//	XMMATRIX world, scale, rot, trans;
	//	scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//	rot = XMMatrixRotationRollPitchYaw(1.0f, 0.0f, 0.0f);
	//	trans = XMMatrixTranslation(0.0f, 2.0f, 0.0f);
	//	world = scale * rot * trans * parentMatrix;
	//	Renderer::SetWorldMatrix(world);

	//	//マテリアル設定
	//	MATERIAL material{};
	//	material.Diffuse = { 1.0f,1.0f,1.0f,1.0f };
	//	material.TextureEnable = true;
	//	Renderer::SetMaterial(material);


	//	//m_ModelRendererChild->Draw();
	//}

}
