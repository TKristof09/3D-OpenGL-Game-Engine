#include "CoreEngine.h"

#include "Window.h"
#include "Time.h"
#include "Input.h"
#include "SDL_Backend.h"
CoreEngine::CoreEngine(int width, int height, double framerate, Game* game, Window* window)
{
	m_isRunning = false;
	m_width = width;
	m_height = height;
	m_frameTime = 1 / framerate;
	m_game = game;
	m_window = window;
}


CoreEngine::~CoreEngine()
{
	m_window->Close();
}

void CoreEngine::CreateWindow(const std::string& title)
{
	m_window->Create(m_width, m_height, title);
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

			if (m_window->IsCloseRequested())
				Stop();

			Time::SetDelta(m_frameTime);
			Input::Update();

			m_game->Input();
			m_game->Update();

			unprocessedTime -= m_frameTime;
		}

		if (render)
		{
			m_window->ClearScreen();
			m_game->Render();
			m_window->Render();
		}
		else
		{
			SDL_Delay(1);
		}
	}
}