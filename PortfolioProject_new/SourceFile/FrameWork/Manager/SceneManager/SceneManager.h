#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

class SceneManager
{
private:
	static class Scene*		m_Scene;
	static class Scene*		m_SceneNext;

	static class FadeQuad*	m_Fader;

public:
	static void			Init();
	static void			Uninit();
	static void			Update();
	static void			Draw();


	static Scene*		GetScene()	{ return m_Scene; }
	static FadeQuad*	GetFade()	{ return m_Fader; }

	template <typename T>
	static void			SetScene()
	{
		m_SceneNext = new T();
	}
};

#endif // SCENEMANAGER_H