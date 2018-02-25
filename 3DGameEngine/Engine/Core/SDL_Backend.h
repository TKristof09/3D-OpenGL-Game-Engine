#ifndef SDL_BACKEND_H
#define SDL_BACKEND_H

void SDLSetIsCloseRequested(bool value);
bool SDLGetIsCloseRequested();
void SDLSetFullScreen(bool value);

void SDLCreateWindow(const char* title, int width, int height, bool fullscreen);
void SDLSwapBuffers();
void SDLDestroyWindow();

#endif // !SDL_BACKEND_H


