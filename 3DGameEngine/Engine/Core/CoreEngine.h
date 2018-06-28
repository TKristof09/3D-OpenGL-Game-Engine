#ifndef COREENGINE_H
#define COREENGINE_H

#include "Game.h"
#include "RenderingEngine.h"
#include "../Physics/PhysicsEngine.h"
#include "../Audio/AudioEngine.h"

class CoreEngine
{
public:
	CoreEngine(int width, int height, double framerate, Game* game);
	~CoreEngine();
	void CreateWindow(const std::string& title);
	void Start();

private:
	void Stop();
	void Run();

	bool m_isRunning;
	int m_width;
	int m_height;
	double m_frameTime;
	Game* m_game;

	RenderingEngine* m_renderingEngine;
	PhysicsEngine* m_physicsEngine;
    AudioEngine* m_audioEngine;
};

#endif // !COREENGINE_H
