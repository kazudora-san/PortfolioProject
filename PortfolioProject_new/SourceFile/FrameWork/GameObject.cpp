#include	"Main.h"
#include	"GameObject.h"

bool GameObject::Destroy()
{
	if (m_Destroy)
	{
		Uninit();
		delete this;
		return true;
	}
	else
	{
		return false;
	}
}

const Vector3& GameObject::GetRight() const
{
	XMMATRIX matrix;
	matrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	Vector3 right;
	XMStoreFloat3((XMFLOAT3*)&right, matrix.r[0]);

	return right;
}

Vector3 GameObject::GetForward()
{
	XMMATRIX matrix;
	matrix = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	Vector3 forward;
	XMStoreFloat3((XMFLOAT3*)&forward, matrix.r[2]);

	return forward;
}

float GameObject::GetDistance(Vector3 Position)
{
	Vector3 direction = m_Position - Position;
	return (m_Position - Position).length();
}

float GameObject::GetZ(Vector3 Position, Vector3 Forward)
{
	Vector3 direction = m_Position - Position;
	return Vector3::dot(direction, Forward);
}
