#pragma once


struct VERTEX_3D
{
	XMFLOAT3 Position;
	XMFLOAT3 Normal;
	XMFLOAT4 Diffuse;
	XMFLOAT2 TexCoord;
};


struct MATERIAL
{
	XMFLOAT4 Ambient;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Specular;
	XMFLOAT4 Emission;

	float Shininess;

	BOOL TextureEnable;

	float Dummy[2];
};


struct LIGHT
{
	BOOL Enable;

	BOOL Dummy[3];

	XMFLOAT4 Direction;
	XMFLOAT4 Diffuse;
	XMFLOAT4 Ambient;

	XMFLOAT4 Position;
	XMFLOAT4 PointLightParam;

	XMFLOAT4 SkyColor;
	XMFLOAT4 GroundColor;
	XMFLOAT4 GroundNormal;

	XMFLOAT4 Angle;
};


class Renderer
{
private:
	static D3D_FEATURE_LEVEL m_FeatureLevel;

	static ID3D11Device* m_Device;
	static ID3D11DeviceContext* m_DeviceContext;

	static IDXGISwapChain* m_SwapChain;

	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer* m_WorldBuffer;
	static ID3D11Buffer* m_ViewBuffer;
	static ID3D11Buffer* m_ProjectionBuffer;
	static ID3D11Buffer* m_MaterialBuffer;
	static ID3D11Buffer* m_LightBuffer;
	static ID3D11Buffer* m_CameraBuffer;

	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	static ID3D11BlendState* m_BlendState;
	static ID3D11BlendState* m_BlendStateAdd;
	static ID3D11BlendState* m_BlendStateATC;

public:
	static void Init();
	static void Uninit();

	static void Begin();
	static void End();

	static void SetDepthEnable(bool enable);
	static void SetATCEnable(bool enable);
	static void SetAddEnable(bool enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(XMMATRIX worldMatrix);
	static void SetViewMatrix(XMMATRIX viewMatrix);
	static void SetProjectionMatrix(XMMATRIX projectionMatrix);
	static void SetMaterial(MATERIAL material);
	static void SetLight(LIGHT light);
	static void SetCameraPosition(Vector3 cameraPosition);

	static void CreateVertexShader(
		ID3D11VertexShader** vertexShader,
		ID3D11InputLayout** vertexLayout,
		const char* fileName
	);

	static void CreatePixelShader(
		ID3D11PixelShader** pixelShader,
		const char* fileName
	);

	static ID3D11Device* GetDevice() { return m_Device; }
	static ID3D11DeviceContext* GetDeviceContext()
	{
		return m_DeviceContext;
	}
};