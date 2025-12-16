#ifndef		GAMEOBJECT_H
#define		GAMEOBJECT_H

#include	"Vector3/Vector3.h"

class GameObject
{
protected:
	bool		m_Destroy	= false;

	Vector3		m_Position	= {};
	Vector3		m_Rotation	= {};
	Vector3		m_Scale		= { 1.0f,1.0f,1.0f };
	Vector3		m_Velocity	= { 0.0f, 0.98f, 0.0f };

public:
	virtual void Init()		= 0;
	virtual void Uninit()	= 0;
	virtual void Update()	= 0;
	virtual void Draw()		= 0;

	void SetDestroy() { m_Destroy = true; }

	bool Destroy();

	Vector3 GetPosition() const { return m_Position; }
	void SetPosition(const Vector3& Position) { m_Position = Position; }

	Vector3 GetRotation() const { return m_Rotation; }
	void SetRotation(const Vector3& Rotation) { m_Rotation = Rotation; }

	Vector3 GetScale() const { return m_Scale; }
	void SetScale(const Vector3& Scale) { m_Scale = Scale; }


	Vector3 GetRight();
	virtual Vector3 GetForward();

	float GetDistance(Vector3 Position);
	float GetZ(Vector3 Position, Vector3 Forward);

};

#endif // GAMEOBJECT_H