#ifndef GAME_H
#define GAME_H

#include "GameObject.h"
#include "../Rendering/DebugDrawer.h"
#include "../Rendering/DebugUI.h"
#include "../Audio/AudioListener.h"

class Game
{
public:
	Game()
        : m_renderingEngine(nullptr),
          m_physicsEngine(nullptr),
          m_audioEngine(nullptr),
          m_debugUI(nullptr)
	{
        m_root = new GameObject("root");
	}

	virtual ~Game()
	{
        delete m_root;
	};
	virtual void Init() = 0;
    
    virtual void Start()
    {
        m_root->Start();
    }

	virtual void Update()
	{
		m_root->Update();
	}

	virtual void Input()
	{
		m_root->Input();
	}

	void SetPhysicsEngine(PhysicsEngine* physicsEngine)
	{
		m_physicsEngine = physicsEngine;
		m_root->SetPhysicsEngine(m_physicsEngine);
	}

    void SetAudioEngine(AudioEngine* audioEngine)
	{
        m_audioEngine = audioEngine;
        m_root->SetAudioEngine(m_audioEngine);
	}

	void SetRenderingEngine(RenderingEngine* renderingEngine)
	{
		m_renderingEngine = renderingEngine;
		m_root->SetRenderingEngine(m_renderingEngine);
	}

	void Render(RenderingEngine* renderingEngine);
    
    void AddToScene(GameObject* gameObject)
    {
        m_root->AddChild(gameObject);
    }

    //TODO find better solution for this
    void AddToDebugUI(DebugUIWindow* window)
    {
        m_debugUI->AddWindow(window);
    }
    void SetDebugUI(DebugUI* ui)
    {
        m_debugUI = ui;
    }

    void SetUpHierarchyUI(DebugUIWindow* window)
    {
        m_root->AddToHierarchyUI(window, nullptr, true);
    }

private:
	GameObject* m_root;
	RenderingEngine* m_renderingEngine;
	PhysicsEngine* m_physicsEngine;
    AudioEngine* m_audioEngine;
    DebugUI* m_debugUI;
};

class BlankGame : public Game
{
public:
    void Init() override
    {
        auto cameraOBJ = new GameObject("camera");
        cameraOBJ->AddComponent(new Camera(
            60.0f, static_cast<float>(*Window::GetWidth()) / static_cast<float>(*Window::GetHeight()), 0.001f, 1000.0f));
        cameraOBJ->AddComponent(new AudioListener());
        AddToScene(cameraOBJ);
    };
};

#endif // !GAME_H
