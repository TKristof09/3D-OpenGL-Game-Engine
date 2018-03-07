#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Transform.h"

class Shader;
class RenderingEngine;
class GameComponent;

class GameObject
{
public:
    GameObject() :m_renderingEngine(nullptr) {};
    ~GameObject() {};
	void Update();
	void Render(const Shader* shader, RenderingEngine* renderingEngine);
	void Input();
	void AddChild(GameObject* child);
	void AddComponent(GameComponent* component);
    void SetRenderingEngine(RenderingEngine* renderingEngine);
	Transform* GetTransform() { return &m_transform; };

private:
	Transform m_transform;
	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_components;
    RenderingEngine* m_renderingEngine;
};

#endif // !GAMEOBJECT_H
