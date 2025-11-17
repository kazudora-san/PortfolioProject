#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"PlayerModel.h"
#include	"Camera/Camera.h"
#include	"Render/Renderer.h"
#include	"Render/ModelRenderer.h"
#include	"Input/Input.h"
#include	"Bullet/Bullet.h"
#include	"Enemy/Enemy.h"
#include	"Scene/Scene.h"
#include	"AnimationModel/AnimationModel.h"
#include	"Field/MeshField/MeshField.h"

void PlayerModel::Init()
{
	//m_ModelRenderer = new ModelRenderer();
	//m_ModelRenderer->Load("asset\\model\\PlayerModel.obj");

	//m_ModelRendererChild = new ModelRenderer();
	//m_ModelRendererChild->Load("asset\\model\\PlayerModel.obj");


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
}

void PlayerModel::Uninit()
{
	//delete m_ModelRenderer;
	//delete m_ModelRendererChild;

	m_AnimationModel->Uninit();
	delete m_AnimationModel;

	m_VertexLayOut->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void PlayerModel::Update()
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


	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Bullet* bullet = SceneManager::GetScene()->AddGameObject<Bullet>(1);
		bullet->SetPosition(m_Position);
		bullet->SetVelocity(GetForward() * 0.5f);

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

void PlayerModel::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//マトリクス設定
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


	m_AnimationModel->Draw();
}
