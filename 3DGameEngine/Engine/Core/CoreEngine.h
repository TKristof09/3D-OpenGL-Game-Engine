#ifndef COREENGINE_H
#define COREENGINE_H

#include "Game.h"
#include "RenderingEngine.h"

class CoreEngine
{
public:
	CoreEngine(int width, int height, double framerate, Game* game);
	~CoreEngine();
	void CreateWindow(const std::string& title);
	void Start();
	void Stop();

private:

	void Run();

	bool m_isRunning;
	int m_width;
	int m_height;
	double m_frameTime;
	Game* m_game;
	RenderingEngine* m_renderingEngine;

};

#endif // !COREENGINE_H


