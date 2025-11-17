#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Render/Renderer.h"

#include	"Scene/Title/Title.h"
#include	"Scene/Scene.h"
#include	"Input/Input.h"
#include	"Camera/Camera.h"
#include	"Render/Polygon2D.h"
#include	"Scene/Game/Game.h"
#include	"Fade/FadeQuad.h"
#include	"Player/PlayerModel/PlayerModel.h"
#include	"Audio/Audio.h"
#include	"Manager/AudioManager/AudioManager.h"
#include	"AnimationModel/AnimationModel.h"

void Title::Init()
{
	AddGameObject<Camera>(0);

	auto* fade = AddGameObject<FadeQuad>(2);
	fade->FadeIn(3.0f);
	AddGameObject<Polygon2D>(2)->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\Title.png");
	// âÊëúÉTÉCÉYÅ@ÇQÇRÇRÅ~ÇUÇO
	AddGameObject<Polygon2D>(2)->Init(SCREEN_WIDTH - 233, SCREEN_HEIGHT - 60, 233, 60, "asset\\texture\\PlessEnter.png");
	AddGameObject<PlayerModel>(3);
	//m_Audio->Load();
	m_Audio->Init();
	m_Audio->Load("asset\\audio\\TitleBGM.wav", "TitleBGM");
	m_Audio->Load("asset\\audio\\PushSE.wav", "PushSE");
	m_Audio->Play("TitleBGM", true);
}


void Title::Update()
{
	if (Input::GetKeyTrigger(VK_RETURN) && !m_IsNextScene)
	{
		m_Frame = 0;
		m_IsNextScene = true;
		m_Audio->Stop("TitleBGM");
		m_Audio->Play("PushSE");
	}
	else
	{
		std::vector<Polygon2D*> pressEnters = SceneManager::GetScene()->GetGameObjects<Polygon2D>();

		if (m_Frame > 60)
		{
			pressEnters[1]->Render();
		}
		else
		{

			pressEnters[1]->NotRender();
		}

		if (m_Frame > 120)
		{
			m_Frame = 0;
		}
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

		m_Audio->Uninit();
	}
}

