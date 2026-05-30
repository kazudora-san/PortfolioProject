#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Scene/Scene.h"
#include	"TitleCamera.h"
#include	"Renderer/Renderer.h"
#include	"Player/Player.h"
#include	"Input/Keyboard.h"
#include	"Input/Input.h"

void TitleCamera::Init()
{
	m_Position = { 0.0f, 3.0f, -5.0f };
}

void TitleCamera::Uninit()
{
}

void TitleCamera::Update()
{
}

void TitleCamera::Draw()
{
	m_MtxPerspective = XMMatrixPerspectiveFovLH(
		1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,
		0.1f,
		500.0f
	);

	Renderer::SetProjectionMatrix(m_MtxPerspective);

	XMFLOAT3 up = { 0.0f, 1.0f, 0.0f };

	m_MtxView = XMMatrixLookAtLH(
		XMLoadFloat3((XMFLOAT3*)&m_Position),
		XMLoadFloat3((XMFLOAT3*)&m_Target),
		XMLoadFloat3(&up)
	);

	Renderer::SetCameraPosition(m_Position);
	Renderer::SetViewMatrix(m_MtxView);
}

Vector3 TitleCamera::GetForward()
{
	Vector3 forward = m_Target - m_Position;
	forward.normalize();

	return forward;
}