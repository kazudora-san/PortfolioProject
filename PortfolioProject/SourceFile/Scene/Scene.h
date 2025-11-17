#ifndef SCENE_H
#define SCENE_H

#include	<list>

#define		LAYER_MAX (4)

class GameObject;

class Scene
{
private:
	std::list<GameObject*>	m_GameObject[LAYER_MAX];//X層のレイヤー

public:
	virtual	void	Init();
	virtual	void	Uninit();
	virtual	void	Update();
	virtual	void	Draw();

	template <typename T>//テンプレート

	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		gameObject->Init();
		m_GameObject[Layer].push_back(gameObject);

		return gameObject;
	}


	template <typename T>//テンプレート

	T* GetGameObject()
	{
		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (auto gameObject : m_GameObject[i])
			{
				T* find = dynamic_cast<T*>(gameObject);
				if (find != nullptr)
					return find;
			}
		}
		return nullptr;
	}

	template <typename T>//テンプレート
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> finds;

		for (int i = 0; i < LAYER_MAX; i++)
		{
			for (auto gameObject : m_GameObject[i])
			{
				T* find = dynamic_cast<T*>(gameObject);
				if (find != nullptr)
					finds.push_back(find);
			}
		}
		return finds;
	}

};

#endif