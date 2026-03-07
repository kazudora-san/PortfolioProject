//-----------------------------
//	DWScene.h[DWSceneクラス制御]
//	千葉知輝
//	作成日 2025/10/10
//-----------------------------

#ifndef DWSCENE_H
#define DWSCENE_H

#include <vector>
#include <string>

#include "DWGameObject.h"
#include "DWVector2/DWVector2.h"

class DWGameObject;
class DWManager;
class DWSceneManager;

constexpr int LayerMax = 6;

// LayerTypeに追加する場合は、LayerMaxも変更する
enum LayerType
{
	BackLayer = 0,
	BlockLayer,
	EnemyLayer,
	BulletLayer,
	PlayerLayer,
	UILayer,
};

class DWScene
{
protected:
	std::vector<DWGameObject*>	GameObjectList[LayerMax] = {};
	std::vector<DWGameObject*>	PendingGameObjectList[LayerMax] = {};
	std::vector<DWManager*>		ManagerList = {};
	DWSceneManager* SceneManager = nullptr;
	std::string					SceneName = {};
	DWVector2					Offset		= {};
	bool						bRestartFlag	= false;

public:
	virtual void	Init()		= 0;
	virtual void	Uninit();
	virtual void	Update();
	virtual void	Draw();

	void	SetOffset(const DWVector2& offset) { Offset = offset; }
	void	SetRestart();

	DWSceneManager*				GetSceneManager()	const	{ return SceneManager; }
	const std::string&			GetSceneName()		const	{ return SceneName; }
	DWGameObject*				GetGameObjectByTag	(const std::string& tag) const;
	std::vector<DWGameObject*>	GetGameObjectsByTag	(const std::string& tag) const;
	DWVector2					GetOffset()			const	{ return Offset; }

	template<typename T>
	T* AddGameObject(int layer)
	{
		T* gameObject = new T();
		GameObjectList[layer].push_back(gameObject);

		if (!gameObject)
		{
			return nullptr;
		}

		gameObject->SetScene(this);
		gameObject->Init();
		return gameObject;
	}

	template<typename T>
	T* AddPendingGameObject(int layer)
	{
		T* gameObject = new T();
		PendingGameObjectList[layer].push_back(gameObject);

		if (!gameObject)
		{
			return nullptr;
		}

		gameObject->SetScene(this);
		gameObject->Init();
		return gameObject;
	}

	void RegistPendingGameObject()
	{
		for (int i = 0; i < LayerMax; i++)
		{
			for (DWGameObject* gameObject : PendingGameObjectList[i])
			{
				if (!gameObject)
				{
					continue;
				}

				GameObjectList[i].push_back(gameObject);
			}

			// 終わったら、リストを初期化しておく
			PendingGameObjectList[i].clear();
		}
	}

	// １つ取得と複数取得でわける
	template<typename T>
	T* GetGameObject()
	{
		for (int i = 0; i < LayerMax; i++)
		{
			for (auto* gameObject : GameObjectList[i])
			{
				if (auto* castGameObject = dynamic_cast<T*>(gameObject))
				{
					if (!castGameObject)
					{
						continue;
					}

					return castGameObject;
				}
			}
		}

		return nullptr;
	}

	// 頻繁に呼ぶと処理が重くなるため注意
	template<typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<DWGameObject*> gameObjects = {};

		for (auto* gameObject : GameObjectList)
		{
			if (auto* castGameObject = dynamic_cast<T*>(gameObject))
			{
				if (!castGameObject)
				{
					continue;
				}

				gameObjects.push_back(castGameObject);
			}
		}

		return gameObjects;
	}

	template<typename T>
	T* AddManager()
	{
		T* manager = new T();
		ManagerList.push_back(manager);

		if (!manager)
		{
			return nullptr;
		}

		manager->SetScene(this);
		manager->Init();
		return manager;
	}

	// １つ取得と複数取得でわける
	template<typename T>
	T* GetManager()
	{
		for (auto* manager : ManagerList)
		{
			if (auto* castManager = dynamic_cast<T*>(manager))
			{
				if (!castManager)
				{
					continue;
				}

				return castManager;
			}
		}

		return nullptr;
	}
};

#endif // DWSCENE_H