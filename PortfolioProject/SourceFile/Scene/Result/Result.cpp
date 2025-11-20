#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Renderer/Renderer.h"
#include	"Scene/Result/Result.h"
#include	"Polygon2D/Polygon2D.h"
#include	"Input/Input.h"
#include	"Scene/Game/Game.h"
#include	"Camera/Camera.h"
#include	"Scene/Title/Title.h"
#include	"Fade/FadeQuad.h"
#include	"Manager/AudioManager/AudioManager.h"

void Result::Init()
{
	AddGameObject<Camera>(0);
	auto* fade = AddGameObject<FadeQuad>(2);
	fade->FadeIn(3.0f);
	AddGameObject<Polygon2D>(2)->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset\\texture\\Result.png");
	// âÊëúÉTÉCÉYÅ@ÇQÇRÇRÅ~ÇUÇO
	AddGameObject<Polygon2D>(2)->Init(SCREEN_WIDTH - 233, SCREEN_HEIGHT - 60, 233, 60, "asset\\texture\\PlessEnter.png");
	// âÊëúÉTÉCÉYÅ@ÇRÇOÇQÅ~ÇTÇV
	AddGameObject<Polygon2D>(2)->Init(SCREEN_WIDTH / 2 - 302 / 2, SCREEN_HEIGHT / 2 - 57 / 2, 302, 57, "asset\\texture\\RankS!.png");
	m_Audio->Init();
	m_Audio->Load("asset\\audio\\ResultBGM.wav", "ResultBGM");
	m_Audio->Play("ResultBGM");
}

void Result::Update()
{
	if (Input::GetKeyTrigger(VK_RETURN))
	{
		if (auto* f = SceneManager::GetFade(); f && !f->IsBusy()) {
			f->FadeOut(0.6f, { 0,0,0 }, []() {
				SceneManager::SetScene<Title>();
				if (auto* g = SceneManager::GetFade()) {
					g->FadeIn(0.6f, { 0,0,0 });
				}
				});
			m_Audio->Uninit();
		}
	}

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
	else
	{
		m_Frame++;
	}
}
