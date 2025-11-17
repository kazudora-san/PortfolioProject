#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Render/Renderer.h"

#include	"Scene/Game/Game.h"
#include	"Camera/Camera.h"
#include	"Field/Field.h"
#include	"Player/Player.h"
#include	"Render/Polygon2D.h"
#include	"Enemy/Enemy.h"
#include	"Scene/Scene.h"
#include	"Input/Input.h"
#include	"Scene/Title/Title.h"
#include	"Field/MeshField/MeshField.h"
#include	"Score/Score.h"
#include	"Skydorm/Skydorm.h"
#include	"Scene/Result/Result.h"
#include	"Fade/FadeQuad.h"
#include	"Wave/Wave.h"
#include	"Tree/Tree.h"
#include	"Grass/Grass.h"
#include	"Rock/Rock.h"

void Game::Init()
{
	AddGameObject<Camera>(0);

	MeshField* meshField = AddGameObject<MeshField>(0);
	AddGameObject<SkyDorm>(0);
	//AddGameObject<Field>(0);
	
	AddGameObject<Wave>(1);
	AddGameObject<Rock>(1);
	AddGameObject<Player>(1);

	for (int i = 0; i < 1; i++)
	{
		Vector3 position;
		position.x = rand() % 100 - 50.0f;
		position.z = rand() % 100 - 50.0f;
		position.y = meshField->GetHeight(position);
		
		Vector3 scale;
		scale.x = 1.0f + ((rand() % 100) / 100.0f);
		scale.y = 1.0f + ((rand() % 100) / 100.0f);
		scale.z = 1.0f;

		auto tree = AddGameObject<Tree>(1);
		tree->SetPosition(position);
		tree->SetScale(scale);
	}

	for (int i = 0; i < 1; i++)
	{
		Vector3 position;
		position.x = rand() % 100 - 50.0f;
		position.z = rand() % 100 - 50.0f;
		position.y = meshField->GetHeight(position);

		Vector3 scale;
		scale.x = 1.0f + ((rand() % 100) / 100.0f);
		scale.y = 1.0f + ((rand() % 100) / 100.0f);
		scale.z = 1.0f;

		auto tree = AddGameObject<Grass>(1);
		tree->SetPosition(position);
		tree->SetScale(scale);
	}

	//AddGameObject<Enemy>(2)->SetPosition({ 2.0f,0.0f,3.0f });
	//AddGameObject<Enemy>(2)->SetPosition({ 0.0f,0.0f,3.0f });
	//AddGameObject<Enemy>(2)->SetPosition({ -2.0f,0.0f,3.0f });
	//AddGameObject<spiralParticle>(2);
	
	//AddGameObject<Bullet>();
	auto* fade = AddGameObject<FadeQuad>(2);
	fade->FadeIn(3.0f);
	AddGameObject<Score>(2);
}

void Game::Update()
{
	Scene::Update();

	auto enemies = SceneManager::GetScene()->GetGameObjects<Enemy>();
	
	if (Input::GetKeyTrigger(VK_RETURN) || (m_NowFrame > m_StopFrame))
	{
		if (auto* f = SceneManager::GetFade(); f && !f->IsBusy()) {
			f->FadeOut(0.6f, { 0,0,0 }, []() {
				SceneManager::SetScene<Result>();
				if (auto* g = SceneManager::GetFade()) {
					g->FadeIn(0.6f, { 0,0,0 });
				}
				});
		}

		
	}

	//if (enemies.size() == 0)
	//{
	//	m_NowFrame++;
	//}
}
