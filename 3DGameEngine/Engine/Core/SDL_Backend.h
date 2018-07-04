#ifndef SDL_BACKEND_H
#define SDL_BACKEND_H
#include <SDL2/SDL.h>

void SDLRequestClose(bool value);
bool SDLGetIsCloseRequested();
void SDLSetFullScreen(bool value);

void SDLCreateWindow(const char* title, int width, int height, bool fullscreen);
void SDLSwapBuffers();
void SDLDestroyWindow();

SDL_Window* GetWindow();
SDL_GLContext* GetContext();

#endif // !SDL_BACKEND_H
