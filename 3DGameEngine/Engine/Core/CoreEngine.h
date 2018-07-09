#ifndef COREENGINE_H
#define COREENGINE_H

#include "Game.h"
#include "RenderingEngine.h"
#include "../Physics/PhysicsEngine.h"
#include "../Audio/AudioEngine.h"
#include "../Rendering/DebugUI.h"
#include <functional>

class CoreEngine
{
public:
	CoreEngine(int width, int height, double framerate);
	~CoreEngine();
    template<typename T>
    void AddGame(const std::string& name);
    void SetGame(Game* game);
	void CreateWindow(const std::string& title);
	void Start();
	void Stop();

    std::function<Game*()> GetGamePointer(const std::string& name);
private:
	void Run();

	bool m_isRunning;
	int m_width;
	int m_height;
	double m_frameTime;
	Game* m_game;
    std::map<std::string, std::function<Game*()>> m_games;

	RenderingEngine* m_renderingEngine;
	PhysicsEngine* m_physicsEngine;
    AudioEngine* m_audioEngine;
    DebugUI* m_debugUI;
    DebugUIWindow* m_hierarchyWindow;
};

template <typename T>
void CoreEngine::AddGame(const std::string& name)
{
    m_games[name] = []() {return new T; };
}

#endif // !COREENGINE_H
