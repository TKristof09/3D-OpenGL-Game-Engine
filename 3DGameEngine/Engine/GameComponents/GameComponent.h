#ifndef GAMECOMPONENT_H
#define GAMECOMPONENT_H

#include "..\Core\Transform.h"
#include "..\Engine\Core\GameObject.h"
#include <iostream>

class RenderingEngine;
class PhysicsEngine;
class AudioEngine;
class Shader;



class GameComponent
{
public:
	GameComponent() : m_parent(nullptr) {};
	virtual ~GameComponent() = default;;

    virtual void Start() {};
	virtual void Input() {};
	virtual void Update() {};
	virtual void Render(const Shader* shader, RenderingEngine* renderingEngine) {};

    virtual void AddToRenderingEngine(RenderingEngine* renderingEngine) {};
	virtual void AddToPhysicsEngine(PhysicsEngine* physicsEngine) {}
    virtual void AddToAudioEngine(AudioEngine* audioEngine) {};

	Transform* GetTransform() { return m_parent->GetTransform(); };
	const Transform& GetTransform() const { return *m_parent->GetTransform(); };

	void SetGameObject(GameObject* parent) { m_parent = parent; };
	GameObject* GetGameObject() const
	{
		return m_parent;
	}

	template<typename T>
	void RequireComponent() const //Call it in the AddToGameObjectCallback
	{
		if(!m_parent->GetComponent<T>())
		{
			std::cerr << GetGameObject()->name <<" doesn't have a component of: " << typeid(T).name() << std::endl;
			assert(false);
		}
	}
	
	virtual void AddToGameObjectCallback(){} 
private:
	GameObject* m_parent;
};

#endif // !GAMECOMPONENT_H
