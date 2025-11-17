#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Render/Renderer.h"
#include	"Input/Input.h"
#include	"Scene/Scene.h"
#include	"Scene/Game/Game.h"
#include	"Scene/Title/Title.h"
#include	"Scene/Result/Result.h"
#include	"Fade/FadeQuad.h"


Scene*		SceneManager::m_Scene		= nullptr;
Scene*		SceneManager::m_SceneNext	= nullptr;
FadeQuad*	SceneManager::m_Fader		= nullptr;

void SceneManager::Init()
{
	Renderer::Init();
	Input::Init();

	m_Fader = new FadeQuad();
	m_Fader->Init();
	m_Fader->FadeIn();

	m_Scene = new Game();
	m_Scene->Init();
}


void SceneManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	if (m_Fader)
	{
		m_Fader->Uninit();
		delete m_Fader;
		m_Fader = nullptr;
	}

	Input::Uninit();
	Renderer::Uninit();
}

void SceneManager::Update()
{
	Input::Update();

	m_Scene->Update();
	m_Fader->Update();
}

void SceneManager::Draw()
{
	Renderer::Begin();
	
	m_Scene->Draw();
	m_Fader->Draw();

	Renderer::End();

	//‰æ–Ê‘JˆÚ
	if (m_SceneNext != nullptr)
	{
		m_Scene->Uninit();
		delete m_Scene;

		m_Scene = m_SceneNext;
		m_Scene->Init();

		m_SceneNext = nullptr;
	}

}
