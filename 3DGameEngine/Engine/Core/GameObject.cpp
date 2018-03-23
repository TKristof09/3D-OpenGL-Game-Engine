#include "GameObject.h"
#include "..\Engine\GameComponents\GameComponent.h"


GameObject::~GameObject()
{
    for (const auto& pair : m_components)
    {
        delete pair.second;
    }
    for (GameObject* child : m_children)
    {
        delete child;
    }
}


void GameObject::AddChild(GameObject* child)
{
    child->SetRenderingEngine(m_renderingEngine);
    child->GetTransform()->SetParent(&m_transform);
    m_children.push_back(child);
}

void GameObject::AddComponent(GameComponent* component)
{
    component->SetParent(this);
    m_components[typeid(*component)] = component;
}



void GameObject::Update() const
{
	for (const auto& pair : m_components)
	{
        pair.second->Update();
	}
	for(GameObject* child : m_children)
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

	for(GameObject* child : m_children)
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
	for(GameObject* child : m_children)
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
            pair.second->AddToEngine(renderingEngine);
        }

        for (GameObject* child : m_children)
        {
            child->SetRenderingEngine(renderingEngine);
        }
    }
}
