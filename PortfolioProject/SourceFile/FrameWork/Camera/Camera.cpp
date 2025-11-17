#include	"Main.h"
#include	"Manager/SceneManager/SceneManager.h"
#include	"Scene/Scene.h"
#include	"Camera/Camera.h"
#include	"Render/Renderer.h"
#include	"Player/Player.h"
#include	"Input/Keyboard.h"
#include	"Input/Input.h"

void Camera::Init()
{
	m_Position = { 0.0f,1.0f,-5.0f };
}

void Camera::Uninit()
{

}

void Camera::Update()
{
	LONG dx = Input::GetMouseDX();
	LONG dy = Input::GetMouseDY();

	if (dx != 0 || dy != 0)
	{
		
		float sensitivity = 0.05f;		// カメラの基本速度
		m_Rotation.y += dx * sensitivity; // 横回転
		m_Rotation.x += dy * sensitivity; // 縦回転

		// ピッチ制限
		if (m_Rotation.x > XM_PIDIV2)  m_Rotation.x = XM_PIDIV2;
		if (m_Rotation.x < -XM_PIDIV2) m_Rotation.x = -XM_PIDIV2;
	}

	Input::OnMouseMove(0, 0);

	if (Input::GetKeyPress(VK_LEFT))
	{
		m_Rotation.y -= 0.1f;
	}
	if (Input::GetKeyPress(VK_RIGHT))
	{
		m_Rotation.y += 0.1f;
	}

	Player* player = SceneManager::GetScene()->GetGameObject<Player>();

	m_Target = player->GetPosition() + Vector3(0.0f, 1.0f, 0.0f);
	//m_Target += GetRight() * 0.5f;

	m_Position = m_Target
		+ Vector3(-sinf(m_Rotation.y),0.5f,-cosf(m_Rotation.y)) * 5.0f;
}

void Camera::Draw()
{
	m_MtxPerspective = XMMatrixPerspectiveFovLH(1.0f,
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,
		0.1f, 500.0f);

	Renderer::SetProjectionMatrix(m_MtxPerspective);

	XMFLOAT3 up = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_MtxView = XMMatrixLookAtLH(XMLoadFloat3((XMFLOAT3*)&m_Position),
		XMLoadFloat3((XMFLOAT3*)&m_Target), XMLoadFloat3(&up));


	// カメラ座標設定
	Renderer::SetCameraPosition(m_Position);
	Renderer::SetViewMatrix(m_MtxView);
}

Vector3 Camera::GetForward()
{
	Vector3 forward = m_Target - m_Position;
	forward.normalize();

	return forward;
}
