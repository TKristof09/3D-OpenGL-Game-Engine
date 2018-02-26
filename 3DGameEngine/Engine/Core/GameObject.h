#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "..\GameComponents\GameComponent.h"
#include "Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Update();
	void Render(const Camera& camera);
	void Input();
	void AddChild(GameObject child);
	void AddComponent(GameComponent* component);

private:
	Transform m_transform;
	std::vector<GameObject> children;
	std::vector<GameComponent*> components;
};

#endif // !GAMEOBJECT_H
