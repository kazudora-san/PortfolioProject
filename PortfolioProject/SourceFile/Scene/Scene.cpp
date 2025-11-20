#include	"Main.h"
#include	"GameObject.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Renderer/Renderer.h"
#include	"Scene/Scene.h"
#include	"Camera/Camera.h"
#include	"Scene/Title/Title.h"

void Scene::Init()
{
	
}


void Scene::Uninit()
{
	for (int i = 0; i < LAYER_MAX; i++)
	{
		for (auto gameObject : m_GameObject[i])//範囲forループ
		{
			gameObject->Uninit();//ポリモーフィズム
			delete gameObject;

		}

		m_GameObject[i].clear();
	}

}

void Scene::Update()
{
	for (int i = 0; i < LAYER_MAX; i++)
	{
		for (auto gameObject : m_GameObject[i])//範囲forループ
		{
			gameObject->Update();//ポリモフィズム
		}
	}

	for (int i = 0; i < LAYER_MAX; i++)
	{
		//ラムダ式
		m_GameObject[i].remove_if([](GameObject* object)
			{
				return object->Destroy();
			});
	}
}

void Scene::Draw()
{

	//Zソート
	Camera* camera = GetGameObject<Camera>();

	if (camera != nullptr)
	{
		Vector3 cameraPosition = camera->GetPosition();
		Vector3 cameraForward = camera->GetForward();


		m_GameObject[1].sort([&](GameObject* object1, GameObject* object2)
			{
				return object1->GetZ(cameraPosition, cameraForward)
						> object2->GetZ(cameraPosition, cameraForward);
			});
	}

	for (int i = 0; i < LAYER_MAX; i++)
	{
		for (auto gameObject : m_GameObject[i])//範囲forループ
		{
			gameObject->Draw();//ポリモーフィズム
		}
	}

}
