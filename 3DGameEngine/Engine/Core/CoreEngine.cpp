#include "CoreEngine.h"

#include "Window.h"
#include "Time.h"
#include "Input.h"

CoreEngine::CoreEngine(int width, int height, double framerate, Game* game):
	m_isRunning(false), m_width(width), m_height(height), m_frameTime(1.0 / framerate), m_game(game), m_renderingEngine(nullptr) 
{
}


CoreEngine::~CoreEngine()
{
	Window::Close();
	if(m_renderingEngine)
		delete m_renderingEngine;
}

void CoreEngine::CreateWindow(const std::string& title)
{
	Window::Create(m_width, m_height, title);
	m_renderingEngine = new RenderingEngine();
}

void CoreEngine::Start()
{
	if (m_isRunning)
		return;

	Run();
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

	m_game->Init();
    m_game->SetRenderingEngine(m_renderingEngine);

	double lastTime = Time::GetTime();
	double unprocessedTime = 0;

	while (m_isRunning)
	{
		bool render = false;

		double startTime = Time::GetTime();
		double passedTime = startTime - lastTime; //deltatime?
		lastTime = startTime;

		unprocessedTime += passedTime;		

		while (unprocessedTime > m_frameTime)
		{
			render = true;

			if (Window::IsCloseRequested())
				Stop();

			Time::SetDelta(m_frameTime);
			Input::Update();

			//m_renderingEngine->Input();
			m_game->Input();
			m_game->Update();

			unprocessedTime -= m_frameTime;
		}

		if (render)
		{
			Window::Render();
			m_game->Render(m_renderingEngine);
		}
		else
		{
			SDL_Delay(1);
		}
	}
}