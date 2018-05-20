#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include "Color.h"
#include "../Rendering/DebugDrawer.h"

class Game
{
public:
	Game()
		: m_renderingEngine(nullptr),
		  m_physicsEngine(nullptr) {}

	virtual ~Game() = default;
	virtual void Init() = 0;

	virtual void Update()
	{
		m_root.Update();
	}


	void SetPhysicsEngine(PhysicsEngine* physicsEngine)
	{
		m_physicsEngine = physicsEngine;
		m_root.SetPhysicsEngine(m_physicsEngine);
	}

	virtual void Input()
	{
		m_root.Input();
	};

	void SetRenderingEngine(RenderingEngine* renderingEngine)
	{
		m_renderingEngine = renderingEngine;
		m_root.SetRenderingEngine(m_renderingEngine);
	};
	void Render(RenderingEngine* renderingEngine);

	void SetAmbientLightColor(const Color& color);
	void SetAmbientLightIntensity(float intensity);


	void AddToScene(GameObject* gameObject) { m_root.AddChild(gameObject); };

private:
	GameObject m_root;
	RenderingEngine* m_renderingEngine;
	PhysicsEngine* m_physicsEngine;
};

#endif // !GAME_H
