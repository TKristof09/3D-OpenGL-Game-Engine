#include "SDL_Backend.h"

static SDL_Window* window;
static SDL_GLContext glContext;
static bool isCloseRequested = false;

void SDLRequestClose(bool value)
{
	isCloseRequested = value;
}


bool SDLGetIsCloseRequested()
{
	return isCloseRequested;
}

void SDLSetFullScreen(bool value)
{
	int mode;
	if (value)
		mode = SDL_WINDOW_FULLSCREEN;
	else
		mode = 0;

	SDL_SetWindowFullscreen(window, mode);
}

void SDLCreateWindow(const char* title, int width, int height, bool fullscreen)
{
	int mode = 0;

	if (fullscreen)
		mode = SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
	                          SDL_WINDOW_OPENGL | mode);
	glContext = SDL_GL_CreateContext(window);
	//SDL_GL_SetSwapInterval(1); This is VSync(i think)
}

void SDLDestroyWindow()
{
	if (!window)
		return;

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
}

SDL_Window* GetWindow()
{
    return window;
}
SDL_GLContext* GetContext()
{
    return &glContext;
}

void SDLSwapBuffers()
{
	SDL_GL_SwapWindow(window);
}
