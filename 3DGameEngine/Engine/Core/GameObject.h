#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "..\GameComponents\GameComponent.h"
#include "Transform.h"
#include "..\Rendering\Shader.h"
#include "RenderingEngine.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Update();
	void Render(Shader* shader, RenderingEngine* renderingEngine);
	void Input();
	void AddChild(GameObject child);
	void AddComponent(GameComponent* component);
	Transform* GetTransform() { return &m_transform; };

private:
	Transform m_transform;
	std::vector<GameObject> children;
	std::vector<GameComponent*> components;
};

#endif // !GAMEOBJECT_H
