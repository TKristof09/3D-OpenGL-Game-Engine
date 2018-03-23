#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <map>
#include <vector>
#include <typeindex>
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
    template<typename T>
    T* GetComponent()
    {
        auto it = m_components.find(std::type_index(typeid(T)));
        if (it != m_components.end())
        {
            return dynamic_cast<T*>(it->second);
        }
        return nullptr;
    }
private:
	Transform m_transform;
	std::vector<GameObject*> m_children;
	std::map<std::type_index,GameComponent*> m_components;
    RenderingEngine* m_renderingEngine;
};

#endif // !GAMEOBJECT_H
