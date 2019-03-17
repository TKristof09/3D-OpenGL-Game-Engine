#include "CoreEngine.h"

#include "Window.h"
#include "Time.h"
#include "Input.h"
#include "LinearMath/btThreads.h"
#include "BulletMultiThreading/btTaskScheduler.h"
#include <iostream>
CoreEngine* engine = nullptr;

CoreEngine::CoreEngine(int width, int height, double framerate):
	m_isRunning(false),
	m_width(width),
	m_height(height),
	m_frameTime(1.0 / framerate),
	m_game(nullptr),
	m_renderingEngine(nullptr),
	m_physicsEngine(nullptr),
    m_audioEngine(nullptr),
    m_debugUI(nullptr)
{
    engine = this;
	glewExperimental = GL_TRUE;

	btITaskScheduler* scheduler = createDefaultTaskScheduler();
	scheduler->setNumThreads(8);
	btSetTaskScheduler(scheduler);
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	m_physicsEngine = new PhysicsEngine(collisionConfiguration, new btCollisionDispatcherMt(collisionConfiguration),
		new btDbvtBroadphase(), new btConstraintSolverPoolMt(8));

    m_audioEngine = new AudioEngine();
}


CoreEngine::~CoreEngine()
{

	Window::Close();
	delete m_renderingEngine;
	delete m_physicsEngine;

}

void LoadGame(Button* button)
{
    engine->SetGame(engine->GetGamePointer(button->GetName())());
}

void CoreEngine::CreateWindow(const std::string& title)
{
	Window::Create(m_width, m_height, title);
	m_renderingEngine = new RenderingEngine();

    m_debugUI = new DebugUI(DARK);
    DebugUIWindow* window = new DebugUIWindow("Games");
    for (auto pair : m_games)
    {
        Button* button = new Button(pair.first);
        button->RegisterCallback(LoadGame);
        window->AddElement(button);
    }
    m_debugUI->AddWindow(window);
    m_hierarchyWindow = new DebugUIWindow("Hierarchy");
    m_debugUI->AddWindow(m_hierarchyWindow);
	
}

void CoreEngine::SetGame(Game* game)
{
    delete m_game;
    m_game = game;

    m_audioEngine->ReInit();
    m_physicsEngine->ReInit();
    m_renderingEngine->ReInit();

    m_game->SetDebugUI(m_debugUI);

    m_game->Init();
    m_renderingEngine->Init();

    m_game->SetRenderingEngine(m_renderingEngine);
    m_game->SetPhysicsEngine(m_physicsEngine);
    m_game->SetAudioEngine(m_audioEngine);

    m_hierarchyWindow->Clear();
    m_game->SetUpHierarchyUI(m_hierarchyWindow);
    m_game->Start();
}


void CoreEngine::Start()
{
	if (m_isRunning)
		return;
    SetGame(new BlankGame());
    if(!m_game)
    {
        std::cerr << "There is no game loaded, please load one before calling start" << std::endl;
    }
	Run();
}

std::function<Game*()> CoreEngine::GetGamePointer(const std::string& name)
{
    auto it = m_games.find(name);
    if (it != m_games.end())
        return m_games[name];
    return nullptr;
}

void CoreEngine::Stop()
{
	if (!m_isRunning)
		return;

	m_isRunning = false;
}

void CoreEngine::Run()
{
	
	m_isRunning = true;


	double lastTime = Time::GetTime();
	double unprocessedTime = 0;


	while (m_isRunning)
	{
		bool render = false;

		double startTime = Time::GetTime();
		double deltaTime = startTime - lastTime; 
		lastTime = startTime;

		unprocessedTime += deltaTime;

		Input::Update();
		m_game->Input();

		//Update on a fixed timestep
		while (unprocessedTime >= m_frameTime)
		{
			render = true;

			if (Window::IsCloseRequested())
				Stop();

			Time::SetDelta(m_frameTime);
			
			m_game->Update();
            m_audioEngine->Update();
			m_physicsEngine->Simulate(m_frameTime);

			unprocessedTime -= m_frameTime;
		}

		if (render)
		{
			Window::Render();
			m_game->Render(m_renderingEngine);
			//DebugLineDrawer::Draw(m_renderingEngine);
            m_debugUI->FrameUpdate();
		}
		else
		{
			SDL_Delay(1);
		}
	}
}
