#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"GameCharacter.h"
#include	"Manager/AudioManager/AudioManager.h"
#include	"Camera/Camera.h"
#include	"Renderer/Renderer.h"
#include	"Renderer/ModelRenderer/ModelRenderer.h"
#include	"Input/Input.h"
#include	"Bullet/Bullet.h"
#include	"Enemy/FighterEnemy/FighterEnemy.h"
#include	"Scene/Scene.h"
#include	"AnimationModel/AnimationModel.h"
#include	"Field/MeshField/MeshField.h"
#include	"Effect/Explosion/Explosion.h"
#include	"Score/Score.h"
#include	"Effect/Heart/Heart.h"

void GameCharacter::Init()
{
	m_Frame = 0;

	//シェーダー読み込み
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayOut,
		"shader\\CSOFile\\UnlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\CSOFile\\UnlitTexturePS.cso");

	m_Enable = true;
}

void GameCharacter::Uninit()
{
	if (m_AnimationModel)
	{
		m_AnimationModel->Uninit();
		delete m_AnimationModel;
		m_AnimationModel = nullptr;
	}

	m_Enable = false;

	m_VertexLayOut->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}

void GameCharacter::Update()
{
}

void GameCharacter::Draw()
{
	if (!m_Enable)
	{
		return;
	}

	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayOut);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//XMMATRIX parentMatrix;

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
}

bool GameCharacter::IsCritical()
{
	return (m_CharacterStatus.GetLuck() > rand() % 100);
}

// 初期ステータスを格納する用
void CharacterStatus::InitCharacterStatus(const CharacterStatus& characterStatus)
{
	m_Health		= characterStatus.m_Health;
	m_MaxHealth		= characterStatus.m_MaxHealth;
	m_MagicPower	= characterStatus.m_MagicPower;
	m_MaxMagicPower	= characterStatus.m_MaxMagicPower;
	m_Attack		= characterStatus.m_Attack;
	m_Defense		= characterStatus.m_Defense;
	m_Agility		= characterStatus.m_Agility;
	m_Luck			= characterStatus.m_Luck;
}

CharacterStatus::CharacterStatus()
{
}

CharacterStatus::CharacterStatus(	int health,		int maxHealth,
									int magicPower,	int maxMagicPower,
									int attack,		int defense,
									int agility,	int luck)
{
	m_Health		= health;
	m_MaxHealth		= maxHealth;
	m_MagicPower	= magicPower;
	m_MaxMagicPower	= maxMagicPower;
	m_Attack		= attack;
	m_Defense		= defense;
	m_Agility		= agility;
	m_Luck			= luck;
}
