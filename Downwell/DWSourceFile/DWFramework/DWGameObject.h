//-----------------------------
//	DWGameObject.h[ゲームオブジェクト管理]
//	千葉知輝
//	作成日 2025/10/06
//-----------------------------

#ifndef DWGAMEOBJECT_H
#define DWGAMEOBJECT_H

#include "DWVector2/DWVector2.h"
#include "DWComponent/DWComponent.h"
#include <string>
#include <list>

class DWScene;
class DWInput;

class DWGameObject
{
protected:
	DWScene*	Scene		= nullptr;
	int			Texture		= -1;							// テクスチャを保存先
	DWVector2	Position	= { 0.0f, 0.0f };				// オブジェクトの座標
	DWVector2	Scale		= { 1.0f, 1.0f };				// オブジェクトの大きさ
	float		Rotation	= 0.0f;							// 右、左回転のみの予定
	std::string	Tag			= {};							// オブジェクトに"タグ"を付ける
	bool		bEnable		= false;						// 画面に表示するかで使う
	bool		bActive		= false;						// オブジェクトが使用されているか
	std::list<DWComponent*> PendingComponentList	= {};	// AddComponentされた時に、一旦いれる場所(仮置き場)
	std::list<DWComponent*> ComponentList			= {};	// RegistComponentされた時に、入れる場所

#ifdef _DEBUG
	//--------------------
	// デバッグ用
	//--------------------
	std::string	StateName_Debug		= {};
#endif

public:
	virtual void Init()			= 0;
	virtual void Uninit();
	virtual void Update();
	virtual void Draw()	const;

	// コンポーネントを待機場所に追加
	template<typename T>
	T* AddComponent()
	{
		T* component = new T();
		PendingComponentList.push_back(component);
		return component;
	}

	template<typename T>
	T* AddComponent(DWGameObject* owner)
	{
		T* component = new T(owner);
		PendingComponentList.push_back(component);
		return component;
	}

	// コンポーネントを登録
	// ※コンポーネントを全てAddしてからRegistを呼ぶ
	void RegistPendingComponent()
	{
		// 保留中のコンポーネントを全て、追加する
		for (auto* component : PendingComponentList)
		{
			// nullチェック
			if (!component)
			{
				continue;
			}

			// 保留中のComponentを全て追加
			ComponentList.push_back(component);
		}

		// 追加したのち、Initを呼ぶ
		for (auto* component : PendingComponentList)
		{
			// nullチェック
			if (!component)
			{
				continue;
			}

			// 追加出来たら初期化処理を呼ぶ
			component->Init();
		}
		
		// 終わったら、リストを初期化しておく
		PendingComponentList.clear();
	}

	// コンポーネントを取得
	template<typename T>
	T* GetComponent()
	{
		// 今回は一つのオブジェクトに対して検索するため
		// 同じComponentが二つ以上あるのはありえない
		// なので、１つ見つけたら終わり
		
		// List分回す
		for (auto* component : ComponentList)
		{
			// このcomponentにクラスがあるかどうか
			// 無いなら、nullptrが帰ってくる
			if (auto* castComponent = dynamic_cast<T*>(component))
			{
				if (!castComponent)
				{
					continue;
				}

				// 見つかった場合
				return castComponent;
			}
		}

		// 見つからない場合
		return nullptr;
	}

	void	SetTexture	(int				texTureNumber)	{ Texture	= texTureNumber; }
	void	SetPosition	(const DWVector2&	position)		{ Position	= position; }
	void	SetScale	(const DWVector2&	scale)			{ Scale		= scale; }
	void	SetRotation	(float				rotation)		{ Rotation	= rotation; }
	void	SetScene	(DWScene*			scene)			{ Scene		= scene; }
	virtual void	SetEnable	(bool enable);
	void	SetActive	(bool isActive)						{ bActive = isActive; }

	const	DWVector2&		GetPosition()	const	{ return Position; }
	const	DWVector2&		GetScale()		const	{ return Scale; }	
	const	std::string&	GetTag()		const	{ return Tag; }
	float					GetRotation()	const	{ return Rotation; }
	DWScene*				GetScene()		const	{ return Scene; }
	DWInput*				GetInput()		const;
	bool					GetEnable()		const	{ return bEnable; }
	bool					GetAvtive()		const	{ return bActive; }

	virtual void	Reset() = 0;
	virtual	void	OnCollision(DWGameObject* gameObject, const DWVector2& overlap) {};
};

#endif // GAMEOBJECT_H