#ifndef GRASSINSTANCE_H
#define GRASSINSTANCE_H

#include "GameObject.h"

class GrassInstance : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_PositionBuffer;
	ID3D11ShaderResourceView* m_PositionSRV;

	ID3D11InputLayout* m_VertexLayout;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;

	ID3D11ShaderResourceView* m_Texture;

	int m_InstanceNum;
public:

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};

#endif // GRASSINSTANCE_H