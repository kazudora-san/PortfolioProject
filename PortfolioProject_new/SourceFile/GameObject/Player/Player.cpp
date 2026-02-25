#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"Player/Player.h"
#include	"Renderer/ModelRenderer/ModelRenderer.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"GameCharacter/StateMachine/StateMachine.h"
#include	"GameCharacter/State/IdleState/IdleState.h"
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
	PlayerIdle = 0,
	PlayerRun,
	PlayerAttack,
	PlayerJump,
};

const char*	AnimationKeyName[]	= { "Idle", "Run", "Attack", "Jump"};
const CharacterStatus PlayerStatus(
	1000,	// HP
	1000,	// MaxHP
	60,		// MP
	60,		// MaxMP
	20,		// 攻撃力
	10,		// 守備力
	5,		// 素早さ
	5		// 運
);

void Player::Init()
{
	GameCharacter::Init();

	m_CharacterStatus.InitCharacterStatus(PlayerStatus);

	m_StateMachine = new StateMachine();
	m_StateMachine->AddState<IdleState>(this);
	
	// GameObjectを継承しているのでdeleteはNG
	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("Asset\\Model\\Player\\Player_Model.fbx");

	m_AnimationModel->LoadAnimation("Asset\\Model\\Player\\Player_Idle.fbx", AnimationKeyName[PlayerIdle]);
	m_AnimationModel->LoadAnimation("Asset\\Model\\Player\\Player_Run.fbx", AnimationKeyName[PlayerRun]);
	m_AnimationModel->LoadAnimation("Asset\\Model\\Player\\Player_Attack.fbx", AnimationKeyName[PlayerAttack]);
	m_AnimationModel->LoadAnimation("Asset\\Model\\Player\\Player_Jump.fbx", AnimationKeyName[PlayerJump]);

	m_AnimationName = AnimationKeyName[PlayerIdle];
	m_AnimationNameNext = AnimationKeyName[PlayerIdle];
	m_AnimationBlend = 0.0f;
	m_Frame = 0;

	m_Audio->Init();
	m_Audio->Load("Asset\\Audio\\GameBGM.wav", "GameBGM");
	//m_Audio->Play("GameBGM", true);
	m_Audio->Load("Asset\\Audio\\Shot.wav", "ShotSE");
	m_Audio->Load("Asset\\Audio\\Run.wav", "RunSE");

	Scene* scene = SceneManager::GetScene();

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

	GameCharacter::Uninit();
}

void Player::Update()
{
	GameCharacter::Update();

	m_StateMachine->Update();

	if (!m_MeshField)
	{
		MeshField* meshField = SceneManager::GetScene()->GetGameObject<MeshField>();
		if (!m_MeshField)
		{
			return;
		}
	}

	float groundY = m_MeshField->GetHeight(m_Position);

	// ジャンプ処理
	if (Input::CommandJump())
	{
		m_Frame = 0;

		if (m_AnimationNameNext != AnimationKeyName[PlayerJump])
		{
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = AnimationKeyName[PlayerJump];
			m_AnimationBlend = 0.0f;
		}
	}

	m_Position.y = groundY;
	
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

void Player::Idle()
{
	// プレイヤーが止まる時、Idleのアニメーションか？
	if (m_AnimationNameNext != AnimationKeyName[PlayerIdle])
	{
		// Idle以外が入ってれば、Idleのアニメーションを入れて、Blendを0.0fにする
		m_AnimationName = m_AnimationNameNext;
		m_AnimationNameNext = AnimationKeyName[PlayerIdle];
		m_AnimationBlend = 0.0f;
		m_Audio->Stop("RunSE");
	}
}

void Player::Attack()
{
	auto enemies = SceneManager::GetScene()->GetGameObjects<FighterEnemy>();
	for (FighterEnemy* enemy : enemies)
	{
		if (!enemy)
		{
			continue;
		}

		CharacterStatus& characterStatus = enemy->GetCharacterStatus();

		Vector3 d = enemy->GetPosition() - m_Position;
		float dist = d.length();

		if (dist <= SearchRadius)
		{
			int hp = characterStatus.GetHealth();

			// ダメージ計算処理
			// 会心の一撃
			if (IsCritical())
			{
				hp -= m_CharacterStatus.GetAttack() * 2;
			}

			unsigned int enemyDefense = characterStatus.GetDefense();
			unsigned int damage = m_CharacterStatus.GetAttack() - enemyDefense * 0.5;
			hp -= damage;

			if (hp <= 0)
			{
				hp = 0;
				enemy->SetDestroy();
			}

			characterStatus.SetHealth(hp);
		}
	}

	if (m_AnimationNameNext != AnimationKeyName[PlayerAttack])
	{
		m_Frame = 0;
		m_AnimationName = m_AnimationNameNext;
		m_AnimationNameNext = AnimationKeyName[PlayerAttack];
		m_AnimationBlend = 0.0f;
	}
}

void Player::Move()
{
	Vector3 rotation = m_Camera->GetRotation();

	if (Input::MoveLeft())
	{
		m_Position += m_Camera->GetRight() * -0.1f;
		m_Rotation.y = rotation.y - XM_PIDIV2;
	}
	if (Input::MoveRight())
	{
		m_Position += m_Camera->GetRight() * 0.1f;
		m_Rotation.y = rotation.y + XM_PIDIV2;
	}
	if (Input::MoveFront())
	{
		Vector3 forward = m_Camera->GetForward();
		forward.y = 0.0f;
		forward.normalize();

		m_Position += forward * 0.1f;
		m_Rotation.y = rotation.y;
	}
	if (Input::MoveBack())
	{
		Vector3 forward = m_Camera->GetForward();
		forward.y = 0.0f;
		forward.normalize();

		m_Position += forward * -0.1f;
		m_Rotation.y = rotation.y + XM_PI;
	}

	// プレイヤーが動くとき、Runのアニメーションか？
	if (m_AnimationNameNext != AnimationKeyName[PlayerRun])
	{
		// Run以外が入ってれば、Runのアニメーションを入れて、Blendを0.0fにする
		m_AnimationName = m_AnimationNameNext;
		m_AnimationNameNext = AnimationKeyName[PlayerRun];
		m_AnimationBlend = 0.0f;
		//m_Audio->Play("RunSE", true);
	}
}
