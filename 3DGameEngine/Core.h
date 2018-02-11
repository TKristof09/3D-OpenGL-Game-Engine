#ifndef CORE_H
#define CORE_H

#include <string>
#include <iostream>
using namespace std;
#include <SDL2\SDL.h>


class Core
{
public:
	Core(int width, int height, const string& title);
	~Core();

	void Clear(float r, float g, float b, float a);
	void Update();

	inline const int* GetWidth() const { return &m_width; };
	inline const int* GetHeight() const { return &m_height; };
	inline bool IsClosed() const { return isClosed; };


private:
	int m_width;
	int m_height;
	SDL_Window* m_window;
	SDL_GLContext m_context;	
	bool isClosed;


};


#endif // !DISPLAY_H

