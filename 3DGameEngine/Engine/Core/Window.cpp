#include "Window.h"
#include <GL\glew.h>
#include <SDL2\SDL.h>
#include "SDL_Backend.h"
#include <iostream>

int Window::m_width = 0;
int Window::m_height = 0;
std::string Window::m_title = "Title";

void Window::Create(int width, int height, const std::string& title)
{
	m_width = width;
	m_height = height;
	m_title = title;

	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDLCreateWindow(m_title.c_str(), m_width, m_height, false);
	
	GLenum result = glewInit();
	if (result != GLEW_OK)
		std::cerr << "Glew failed to initialize!" << std::endl;
	



	printf("OpenGL version supported by this platform (%p): \n", glGetString(GL_VERSION));

}

void Window::Close()
{
	SDLDestroyWindow();
	SDL_Quit();
	SDL_Quit();
}

void Window::Render()
{
	SDLSwapBuffers();
}

bool Window::IsCloseRequested()
{
	return SDLGetIsCloseRequested();
}

void Window::SetFullScreen(bool value)
{
	SDLSetFullScreen(value);
}
