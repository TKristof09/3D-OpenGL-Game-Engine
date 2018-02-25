#ifndef COREENGINE_H
#define COREENGINE_H

#include <string>
#include "Game.h"
#include "Window.h"

class CoreEngine
{
public:
	CoreEngine(int width, int height, double framerate, Game* game, Window* window);
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
	Window* m_window;

};

#endif // !COREENGINE_H


