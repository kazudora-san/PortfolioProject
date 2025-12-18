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
#include	<random>

enum PlayerAnimatyonKey
{
	Player_Idle = 0,
	Player_Run,
	Player_Attack,
	Player_Jump,
};

const char*	AnimationKeyName[]	= { "Idle", "Run", "Attack", "Jump"};

void Player::Init()
{
	GameCharacter::Init();

	// 初期ステータス
	m_Health		= 100;
	m_MaxHealth		= 100;
	m_MasicPower	= 60;
	m_MaxMasicPower	= 60;
	m_Attack		= 20;
	m_Defense		= 10;
	m_Agility		= 5;
	m_Luck			= 5;

	m_Money = new Score();
	m_Money->Init();

	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("Asset\\Model\\Player\\Player_Model.fbx");


	m_AnimationModel->LoadAnimation("Asset\\Model\\Player\\Player_Idle.fbx",	AnimationKeyName[Player_Idle]);
	m_AnimationModel->LoadAnimation("Asset\\Model\\Player\\Player_Run.fbx",		AnimationKeyName[Player_Run]);
	m_AnimationModel->LoadAnimation("Asset\\Model\\Player\\Player_Attack.fbx",	AnimationKeyName[Player_Attack]);
	m_AnimationModel->LoadAnimation("Asset\\Model\\Player\\Player_Jump.fbx",	AnimationKeyName[Player_Jump]);

	m_AnimationName = AnimationKeyName[Player_Idle];
	m_AnimationNameNext = AnimationKeyName[Player_Idle];
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

	m_Scale = {0.01f,0.01f,0.01f };
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
	/*if (Input::CommandAction())
	{
		m_Frame = 0;

		if (m_AnimationNameNext != AnimationKeyName[Player_Attack])
		{
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = AnimationKeyName[Player_Attack];
			m_AnimationBlend = 0.0f;
		}

		Attack();
		m_IsAttack = true;
	}*/

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
		m_Frame = 0;

		if (m_AnimationNameNext != AnimationKeyName[Player_Jump])
		{
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = AnimationKeyName[Player_Jump];
			m_AnimationBlend = 0.0f;
		}
	}

	// 通常時は地形に沿う
	m_Position.y = groundY;

	if (m_IsAttack)
	{
		if (m_AnimationNameNext != AnimationKeyName[Player_Attack])
		{
			// Run以外が入ってれば、Runのアニメーションを入れて、Blendを0.0fにする
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = AnimationKeyName[Player_Attack];
			m_AnimationBlend = 0.0f;
			//m_Audio->Play("RunSE", true);
		}

		if (m_Frame >= 120)
		{
			m_IsAttack = false;
		}
	}
	else if (move)
	{
		// プレイヤーが動くとき、Runのアニメーションか？
		if (m_AnimationNameNext != AnimationKeyName[Player_Run])
		{
			// Run以外が入ってれば、Runのアニメーションを入れて、Blendを0.0fにする
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = AnimationKeyName[Player_Run];
			m_AnimationBlend = 0.0f;
			//m_Audio->Play("RunSE", true);
		}
	}
	else
	{
		// プレイヤーが止まる時、Idleのアニメーションか？
		if (m_AnimationNameNext != AnimationKeyName[Player_Idle])
		{
			// Idle以外が入ってれば、Idleのアニメーションを入れて、Blendを0.0fにする
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = AnimationKeyName[Player_Idle];
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
}

void Player::Attack()
{
	Scene* scene = SceneManager::GetScene();
	if (!scene || m_IsAttack)
	{
		return;
	}

	auto enemies = scene->GetGameObjects<FighterEnemy>();

	for (FighterEnemy* enemy : enemies)
	{
		if (!enemy)
		{
			continue;
		}

		Vector3 d = enemy->GetPosition() - m_Position;
		float dist = d.length();

		if (dist <= SearchRadius)
		{
			int hp = enemy->GetHealth();

			// ダメージ計算処理
			// 会心の一撃
			if (IsCritical())
			{
				hp -= m_Attack * 2;
			}

			unsigned int enemyDefense = enemy->GetDefense();
			unsigned int damage = m_Attack - enemyDefense / 2;
			hp -= damage;

			if (hp <= 0)
			{
				hp = 0;
				enemy->SetDestroy();
			}

			enemy->SetHealth(hp);
		}
	}

	if (m_AnimationNameNext != AnimationKeyName[Player_Attack])
	{
		m_Frame = 0;
		m_AnimationName = m_AnimationNameNext;
		m_AnimationNameNext = AnimationKeyName[Player_Attack];
		m_AnimationBlend = 0.0f;
	}

	m_IsAttack = true;
}