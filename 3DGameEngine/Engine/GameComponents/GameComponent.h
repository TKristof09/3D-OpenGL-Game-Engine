#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include "..\Core\Transform.h"
#include "..\Engine\Core\GameObject.h"

class RenderingEngine;
class Shader;

class GameComponent
{
public:
    GameComponent() :m_parent(0) {};
    virtual ~GameComponent() {};

    virtual void Input() {};
    virtual void Update() {};
    virtual void Render(const Transform& transform, const Shader* shader, RenderingEngine* renderingEngine) {};
    virtual void AddToEngine(RenderingEngine* renderingEngine) {};
    
    inline Transform* GetTransform() { return m_parent->GetTransform(); };
    inline const Transform& GetTransform() const { return *m_parent->GetTransform(); };

    virtual void SetParent(GameObject* parent) { m_parent = parent; };

private:
    GameObject* m_parent;
};

#endif // !GAMECOMPONENT_H
