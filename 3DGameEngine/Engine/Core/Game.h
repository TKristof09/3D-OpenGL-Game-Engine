#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include "RenderingEngine.h"

class Game
{
public:
	virtual ~Game() = default;
	virtual void Init() = 0;
	virtual void Update()
	{
		m_root.Update();
	};
	virtual void Input()
	{
		m_root.Input();
	};
    void Render(RenderingEngine* renderingEngine)
    {
        renderingEngine->Render(m_root);
    }
    void SetRenderingEngine(RenderingEngine* renderingEngine) { m_root.SetRenderingEngine(renderingEngine); };

    void AddToScene(GameObject* gameObject) { m_root.AddChild(gameObject); };

private:
	GameObject m_root;

};

#endif // !GAME_H

