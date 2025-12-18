#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"EnemyBase.h"
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

void EnemyBase::Init()
{
	GameCharacter::Init();
}

void EnemyBase::Uninit()
{
	GameCharacter::Uninit();
}

void EnemyBase::Update()
{
	GameCharacter::Update();
}

void EnemyBase::Draw()
{
	GameCharacter::Draw();
}
