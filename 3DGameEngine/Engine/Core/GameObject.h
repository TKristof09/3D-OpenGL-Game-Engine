#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "Transform.h"  

class RenderingEngine;
class Shader;
class GameComponent;

class GameObject
{
public:
    GameObject():
        m_renderingEngine(nullptr) {};
    ~GameObject() = default;;
	void Update() const;
	void Render(const Shader* shader, RenderingEngine* renderingEngine) const;
	void Input() const;
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
