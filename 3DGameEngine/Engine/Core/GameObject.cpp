#include "GameObject.h"



GameObject::GameObject()
{
	
}


GameObject::~GameObject()
{
	
}

void GameObject::AddChild(GameObject child)
{
	children.push_back(child);
}

void GameObject::AddComponent(GameComponent* component)
{
	components.push_back(component);
}

void GameObject::Update()
{
	for (GameComponent* component : components)
	{
		component->Update();
	}
	for(GameObject child : children)
	{
		child.Update();
	}
}
void GameObject::Render(const Camera& camera)
{
	for (GameComponent* component : components)
	{
		component->Render(m_transform, camera);
	}

	for(GameObject child : children)
	{
		child.Render(camera);
	}
}
void GameObject::Input()
{
	for (GameComponent* component : components)
	{
		component->Input();
	}
	for(GameObject child : children)
	{
		child.Input();
	}
}
