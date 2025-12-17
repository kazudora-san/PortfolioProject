#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"Player/Player.h"
#include	"Renderer/ModelRenderer/ModelRenderer.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Manager/AudioManager/AudioManager.h"
#include	"Camera/Camera.h"
#include	"Input/Input.h"
#include	"Bullet/Bullet.h"
#include	"Enemy/FighterEnemy/FighterEnemy.h"
#include	"Scene/Scene.h"
#include	"AnimationModel/AnimationModel.h"
#include	"Field/MeshField/MeshField.h"
#include	"Effect/Explosion/Explosion.h"
#include	"Score/Score.h"
#include	"Effect/Heart/Heart.h"

enum AnimatyonKey
{
	Idle = 0,
	Run,
	Attack,
};
const char* AnimationKeyName[] = { "Idle", "Run", "Attack" };

void Player::Init()
{
	GameCharacter::Init();

	m_Money = new Score();
	m_Money->Init();

	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("Asset\\model\\OtamesiModel.fbx");


	m_AnimationModel->LoadAnimation("Asset\\model\\OtamesiIdle.fbx",	AnimationKeyName[Idle]);
	m_AnimationModel->LoadAnimation("Asset\\model\\OtamesiRun.fbx",		AnimationKeyName[Run]);

	m_AnimationName = AnimationKeyName[Idle];
	m_AnimationNameNext = AnimationKeyName[Idle];
	m_AnimationBlend = 0.0f;
	m_Frame = 0;

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"Shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"Shader\\CSOFile\\UnlitTexturePS.cso");
	
	m_Audio->Init();
	m_Audio->Load("Asset\\Audio\\GameBGM.wav", "GameBGM");
	//m_Audio->Play("GameBGM", true);
	m_Audio->Load("Asset\\Audio\\Shot.wav", "ShotSE");
	m_Audio->Load("Asset\\Audio\\Run.wav", "RunSE");

	Scene* scene = SceneManager::GetScene();
	if (!scene)
	{
		return;
	}

	m_Camera = scene->GetGameObject<Camera>();
	if (!m_Camera)
	{
		return;
	}

	m_MeshField = scene->GetGameObject<MeshField>();
	if (!m_MeshField)
	{
		return;
	}
}

void Player::Uninit()
{
	if (m_Audio)
	{
		m_Audio->Uninit();
	}

	if (m_Money)
	{
		m_Money->Uninit();
		delete m_Money;
		m_Money = nullptr;
	}

	GameCharacter::Uninit();
}

void Player::Update()
{
	GameCharacter::Update();

	if (!m_Camera)
	{
		return;
	}
	Vector3 rotation = m_Camera->GetRotation();

	bool move = false;

	if (Input::MoveLeft())
	{
		m_Position += m_Camera->GetRight() * -0.1f;
		m_Rotation.y = rotation.y - XM_PIDIV2;
		move = true;
	}
	if (Input::MoveRight())
	{
		m_Position += m_Camera->GetRight() * 0.1f;
		m_Rotation.y = rotation.y + XM_PIDIV2;
		move = true;
	}
	if (Input::MoveFront())
	{
		Vector3 forward = m_Camera->GetForward();
		forward.y = 0.0f;
		forward.normalize();
		m_Position += forward * 0.1f;
		m_Rotation.y = rotation.y;
		move = true;
	}
	if (Input::MoveBack())
	{
		Vector3 forward = m_Camera->GetForward();
		forward.y = 0.0f;
		forward.normalize();

		m_Position += forward * -0.1f;
		m_Rotation.y = rotation.y + XM_PI;
		move = true;
	}
	if (Input::CommandAction())
	{
		Scene* scene = SceneManager::GetScene();
		if (!scene)
		{
			return;
		}

		Bullet* bullet = scene->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position);
		bullet->SetVelocity(GetForward() * 0.5f);
	}

	if (!m_MeshField)
	{
		Scene* scene = SceneManager::GetScene();
		if (!scene)
		{
			return;
		}

		MeshField* meshField = scene->GetGameObject<MeshField>();
		if (!m_MeshField)
		{
			return;
		}
	}

	float groundY = m_MeshField->GetHeight(m_Position);

	// ジャンプ処理
	if (Input::CommandJump() && !m_IsJump)
	{
		m_JumpTime = 0.0f;
		m_IsJump = true;
	}

	// ジャンプ中
	if (m_IsJump)
	{
		//衝突判定
		auto enemies = SceneManager::GetScene()->GetGameObjects<FighterEnemy>();
		bool particle = false;

		// 当たり判定処理
		for (auto enemy : enemies)
		{
			if (!enemy)
			{
				continue;
			}

			Vector3 d = enemy->GetPosition() - m_Position;
			float length = d.length();
			if (length < 1.0f && !particle)
			{
				SceneManager::GetScene()->AddGameObject<Explosion>(1)->
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


	if (Input::CommandAction())
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
		if (m_AnimationNameNext != AnimationKeyName[Run])
		{
			// Run以外が入ってれば、Runのアニメーションを入れて、Blendを0.0fにする
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = AnimationKeyName[Run];
			m_AnimationBlend = 0.0f;
			//m_Audio->Play("RunSE", true);
		}
	}
	else
	{
		// プレイヤーが止まる時、Idleのアニメーションか？
		if (m_AnimationNameNext != AnimationKeyName[Idle])
		{
			// Idle以外が入ってれば、Idleのアニメーションを入れて、Blendを0.0fにする
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = AnimationKeyName[Idle];
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
	GameCharacter::Draw();

	m_AnimationModel->Draw();

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

void Player::Attack()
{
	if (Input::CommandAction())
	{

	}
}
