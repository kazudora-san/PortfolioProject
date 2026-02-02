#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"FighterEnemy.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Camera/Camera.h"
#include	"Scene/Scene.h"
#include	"AnimationModel/AnimationModel.h"
#include	"Input/Input.h"
#include	"Player/Player.h"

const Vector3 FighterEnemyScale = { 0.01f, 0.01f, 0.01f };
const CharacterStatus FighterEnemyStatus(
	100,	// HP
	100,	// MaxHP
	60,		// MP
	60,		// MaxMP
	20,		// 攻撃力
	10,		// 守備力
	5,		// 素早さ
	5		// 運
);

void FighterEnemy::Init()
{
	EnemyBase::Init();

	// 初期ステータスを必ず入れる
	m_CharacterStatus.InitCharacterStatus(FighterEnemyStatus);

	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("Asset\\Model\\Enemy_Model.fbx");

	m_AnimationModel->LoadAnimation("Asset\\Model\\Enemy_Idle.fbx", "Idle");
	m_AnimationModel->LoadAnimation("Asset\\Model\\Enemy_Attack.fbx", "Attack");
	m_AnimationName = "Idle";
	m_AnimationNameNext = "Idle";
	m_AnimationBlend = 0.0f;
	m_Frame = 0;

	m_Scale = FighterEnemyScale;
	m_Position.y += 1.0f;
}

void FighterEnemy::Uninit()
{
	delete m_AnimationModel;

	EnemyBase::Uninit();
}

void FighterEnemy::Update()
{
	Scene* scene = SceneManager::GetScene();
	if (!scene)
	{
		return;
	}

	Player* player = scene->GetGameObject<Player>();
	if (!player)
	{
		return;
	}
	// エネミー → プレイヤー の方向ベクトル
	Vector3 dir = player->GetPosition() - m_Position;
	dir.y = 0.0f;       // 高さは無視してXZ平面だけで向き
	dir.normalize();

	// Y軸回転（Yaw）を計算
	m_Rotation.y = atan2f(dir.x, dir.z);  // 左手座標系

	if (m_AnimationNameNext != "Idle")
	{
		// Idle以外が入ってれば、Idleのアニメーションを入れて、Blendを0.0fにする
		m_AnimationName = m_AnimationNameNext;
		m_AnimationNameNext = "Idle";
		m_AnimationBlend = 0.0f;
	}

	if (Input::CommandAction())
	{
		if (m_AnimationNameNext != "Attack")
		{
			m_AnimationName = m_AnimationNameNext;
			m_AnimationNameNext = "Attack";
			m_AnimationBlend = 0.0f;
			m_Frame = 0;
		}

		Attack();
	}

	// std::string型には、c_str()というconst char*型に変換してくれる！
	// 二つ入れることで、合成（ブレンド）をしてくれる！（処理は中身を参照）
	m_AnimationModel->Update(m_AnimationName.c_str(), m_Frame,
		m_AnimationNameNext.c_str(), m_Frame,
		m_AnimationBlend);
	m_Frame++;

	m_AnimationBlend += 0.007f;
	if (m_AnimationBlend > 1.0f)
	{
		// 線形補間
		m_AnimationBlend = 1.0f;
	}
}

void FighterEnemy::Draw()
{
	EnemyBase::Draw();

	m_AnimationModel->Draw();
}

void FighterEnemy::Attack()
{
	Scene* scene = SceneManager::GetScene();
	if (!scene)
	{
		return;
	}

	Player* player = scene->GetGameObject<Player>();
	if (!player)
	{
		return;
	}

	Vector3 d = player->GetPosition() - m_Position;
	float dist = d.length();

	if (dist <= SearchRadius)
	{
		CharacterStatus& characterStatus = player->GetCharacterStatus();

		int hp = characterStatus.GetHealth();

		// ダメージ計算処理
		// 会心の一撃
		if (IsCritical())
		{
			hp -= m_CharacterStatus.GetAttack() * 2;
		}

		unsigned int enemyDefense = characterStatus.GetDefense();
		unsigned int damage = m_CharacterStatus.GetAttack() * 4 - enemyDefense / 2;
		hp -= damage;

		if (hp <= 0)
		{
			hp = 0;
			player->SetDestroy();
		}

		characterStatus.SetHealth(hp);
	}
}

void FighterEnemy::Idle()
{
}

void FighterEnemy::Move()
{
}
