#include	"Main.h"
#include	"Renderer/Renderer.h"
#include	"FighterEnemy.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Camera/Camera.h"
#include	"Scene/Scene.h"
#include	"AnimationModel/AnimationModel.h"
#include	"Input/Input.h"

void FighterEnemy::Init()
{
	EnemyBase::Init();

	m_AnimationModel = new AnimationModel();
	m_AnimationModel->Load("Asset\\Model\\Enemy_Tpose.fbx");

	m_AnimationModel->LoadAnimation("Asset\\Model\\Enemy_Idle.fbx", "Idle");
	m_AnimationModel->LoadAnimation("Asset\\Model\\Enemy_Attack.fbx", "Attack");
	m_AnimationName = "Idle";
	m_AnimationNameNext = "Idle";
	m_AnimationBlend = 0.0f;
	m_Frame = 0;

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"Shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"Shader\\CSOFile\\UnlitTexturePS.cso");

	m_Scale = { 0.01f, 0.01f, 0.01f };
	m_Position.y += 1.0f;
}

void FighterEnemy::Uninit()
{
	delete m_AnimationModel;

	EnemyBase::Uninit();
}

void FighterEnemy::Update()
{
	Camera* camera = SceneManager::GetScene()->GetGameObject<Camera>();

	Vector3 rotation = camera->GetRotation();

	m_Rotation.y = rotation.y;

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
		}
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
