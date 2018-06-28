#include "GameObject.h"
#include "../Engine/GameComponents/GameComponent.h"
#include "../GameComponents/Collider.h"


GameObject* GameObject::AddChild(GameObject* child)
{
	child->SetRenderingEngine(m_renderingEngine);
	child->GetTransform()->SetParent(&m_transform);
	m_children.push_back(child);
	return child;
}

void GameObject::AddComponent(GameComponent* component)
{
	component->SetGameObject(this);
	component->AddToGameObjectCallback();
	//TODO find better way
	Collider* temp = dynamic_cast<Collider*>(component);
	if(temp)
		m_components[typeid(Collider)] = component;
	else
		m_components[typeid(*component)] = component;
}


void GameObject::Start() const
{
    for (const auto& pair : m_components)
    {
        pair.second->Start();
    }
    for (GameObject* child : m_children)
    {
        child->Start();
    }
}

void GameObject::Update() const
{
	for (const auto& pair : m_components)
	{
		pair.second->Update();
	}
	for (GameObject* child : m_children)
	{
		child->Update();
	}
}

void GameObject::Render(const Shader* shader, RenderingEngine* renderingEngine) const
{
	for (const auto& pair : m_components)
	{
		pair.second->Render(shader, renderingEngine);
	}

	for (GameObject* child : m_children)
	{
		child->Render(shader, renderingEngine);
	}
}

void GameObject::Input() const
{
	for (const auto& pair : m_components)
	{
		pair.second->Input();
	}
	for (GameObject* child : m_children)
	{
		child->Input();
	}
}

void GameObject::SetRenderingEngine(RenderingEngine* renderingEngine)
{
	if (m_renderingEngine != renderingEngine)
	{
		m_renderingEngine = renderingEngine;

		for (const auto& pair : m_components)
		{
			pair.second->AddToRenderingEngine(renderingEngine);
		}

		for (auto child : m_children)
		{
			child->SetRenderingEngine(renderingEngine);
		}
	}
}

void GameObject::SetPhysicsEngine(PhysicsEngine* physicsEngine)
{
	if(m_physicsEngine != physicsEngine)
	{
		m_physicsEngine = physicsEngine;
		for (const auto& pair : m_components)
		{
			pair.second->AddToPhysicsEngine(physicsEngine);
		}
		for (auto child : m_children)
		{
			child->SetPhysicsEngine(physicsEngine);
		}

	}
}

void GameObject::SetAudioEngine(AudioEngine* audioEngine)
{
    if(m_audioEngine != audioEngine)
    {
        m_audioEngine = audioEngine;
        for (const auto& pair : m_components)
        {
            pair.second->AddToAudioEngine(audioEngine);
        }
        for (auto child : m_children)
        {
            child->SetAudioEngine(audioEngine);
        }
    }
}
