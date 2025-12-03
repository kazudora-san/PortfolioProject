#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
protected:

	GameObject* m_GameObject = nullptr;

public:
	Component() = default;
	Component(GameObject* Object);
	virtual ~Component() {}

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};

};

#endif // COMPONENT_H