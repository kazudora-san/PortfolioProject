#pragma once

#include "Component/Component.h"
#include "Renderer/Renderer.h"
#include <string>
#include <unordered_map>


// マテリアル構造体
struct MODEL_MATERIAL
{
	char Name[256];

	MATERIAL Material;

	char TextureName[256];

	ID3D11ShaderResourceView* Texture;
};


// 描画サブセット構造体
struct SUBSET
{
	unsigned int StartIndex;
	unsigned int IndexNum;

	MODEL_MATERIAL Material;
};


// モデル構造体
struct MODEL_OBJ
{
	VERTEX_3D* VertexArray;
	unsigned int VertexNum;

	unsigned int* IndexArray;
	unsigned int IndexNum;

	SUBSET* SubsetArray;
	unsigned int SubsetNum;
};


struct MODEL
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;

	SUBSET* SubsetArray;
	unsigned int SubsetNum;
};


class ModelRenderer : public Component
{
private:
	static std::unordered_map<std::string, MODEL*> m_ModelPool;

	MODEL* m_Model = {};

	static void LoadModel(const char* fileName, MODEL* model);
	static void LoadObj(const char* fileName, MODEL_OBJ* modelObj);

	static void LoadMaterial(
		const char* fileName,
		MODEL_MATERIAL** materialArray,
		unsigned int* materialNum
	);

public:
	static void Preload(const char* fileName);

	static void UnloadAll();

	void Load(const char* fileName);

	void Draw() override;

	using Component::Component;
};