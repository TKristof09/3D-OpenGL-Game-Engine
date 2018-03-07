#include "GameObject.h"
#include "..\Engine\GameComponents\GameComponent.h"




void GameObject::AddChild(GameObject* child)
{
    child->SetRenderingEngine(m_renderingEngine);
    m_children.push_back(child);
}

void GameObject::AddComponent(GameComponent* component)
{
    component->SetParent(this);
    m_components.push_back(component);
}

void GameObject::Update()
{
	for (GameComponent* component : m_components)
	{
		component->Update();
	}
	for(GameObject* child : m_children)
	{
		child->Update();
	}
}
void GameObject::Render(const Shader* shader, RenderingEngine* renderingEngine)
{
	for (GameComponent* component : m_components)
	{
		component->Render(shader, renderingEngine);
	}

	for(GameObject* child : m_children)
	{
		child->Render(shader, renderingEngine);
	}
}
void GameObject::Input()
{
	for (GameComponent* component : m_components)
	{
		component->Input();
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

        for (GameComponent* component : m_components)
        {
            component->AddToEngine(renderingEngine);
        }

        for (GameObject* child : m_children)
        {
            child->SetRenderingEngine(renderingEngine);
        }
    }
}
