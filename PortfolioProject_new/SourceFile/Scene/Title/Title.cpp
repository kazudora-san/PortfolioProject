#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Renderer/Renderer.h"

#include	"Scene/Title/Title.h"
#include	"Scene/Scene.h"
#include	"Input/Input.h"
#include	"TitleCamera/TitleCamera.h"
#include	"Renderer/Polygon2D/Polygon2D.h"
#include	"Scene/Game/Game.h"
#include	"Fade/FadeQuad.h"
#include	"Player/PlayerModel/PlayerModel.h"
#include	"Audio/Audio.h"
#include	"Manager/AudioManager/AudioManager.h"
#include	"AnimationModel/AnimationModel.h"
#include	"TitleMeshField/TitleMeshField.h"
#include	"TitlePlayer/TitlePlayer.h"
#include	"TitleEnemy/TitleEnemy.h"
#include	"SkyDorm/Skydorm.h"

constexpr float TitleTextureWidth = 378.0f;
constexpr float TitleTextureHeight = 378.0f;

void Title::Init()
{
	Scene::Init();

	AddGameObject<TitleCamera>(0);
	AddGameObject<TitleMeshField>(0);
	SkyDorm* skyDorm = AddGameObject<SkyDorm>(0);
	skyDorm->SetPosition({ 0.0f, 0.0f, 0.0f });

	auto* fade = AddGameObject<FadeQuad>(2);
	fade->FadeIn(3.0f);
	
	AddGameObject<TitlePlayer>(2);

	TitleEnemy* titleEnemy = AddGameObject<TitleEnemy>(2);
	if(!titleEnemy)
	{
		return;
	}
	titleEnemy->SetScale({ 0.5f, 0.5f, 0.5f });
	titleEnemy->SetRotation({ 0.0f, 90.0f, 0.0f });
	titleEnemy->SetPosition({ -2.0f, 0.0f, -1.0f });

	titleEnemy = AddGameObject<TitleEnemy>(2);
	if (!titleEnemy)
	{
		return;
	}
	titleEnemy->SetScale({ 0.5f, 0.5f, 0.5f });
	titleEnemy->SetRotation({ 0.0f, 90.0f, 0.0f });
	titleEnemy->SetPosition({ -1.5f, 0.0f, 0.0f });

	// 2DÉ|ÉäÉSÉìÇÕÉåÉCÉÑÅ[î‘çÜÇÕàÍî‘å„ÇÎÇ≈Ç®äËÇ¢ÇµÇ‹Ç∑
	AddGameObject<Polygon2D>(3)->Init(SCREEN_WIDTH / 2.0f - TitleTextureWidth, -TitleTextureHeight / 2.0f, 
										TitleTextureWidth * 2.0f, TitleTextureHeight * 2.0f, 
										"Asset\\Texture\\Title.png");
	AddGameObject<Polygon2D>(3)->Init(SCREEN_WIDTH / 2.0f - TitleTextureWidth / 2.0f, TitleTextureHeight,
										TitleTextureWidth, TitleTextureHeight,
										"Asset\\Texture\\PressEnter.png");

	//m_Audio->Load();
	//m_Audio->Init();
	//m_Audio->Load("Asset\\Audio\\TitleBGM.wav", "TitleBGM");
	//m_Audio->Load("Asset\\Audio\\PushSE.wav", "PushSE");
	//m_Audio->Play("TitleBGM", true);
}


void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_RETURN) && !m_IsNextScene)
	{
		m_Frame = 0;
		m_IsNextScene = true;
		//m_Audio->Stop("TitleBGM");
		//m_Audio->Play("PushSE");
	}
	else
	{
		
	}

	m_Frame++;

	if (m_Frame > m_StopFrame && m_IsNextScene)
	{
		if (auto* f = SceneManager::GetFade(); f && !f->IsBusy()) {
			f->FadeOut(0.6f, { 0,0,0 }, []() {
				SceneManager::SetScene<Game>();
				if (auto* g = SceneManager::GetFade()) {
					g->FadeIn(0.6f, { 0,0,0 });
				}
				});
		}

		//m_Audio->Uninit();
	}
}

