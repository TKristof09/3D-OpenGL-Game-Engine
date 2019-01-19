#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

// TODO mouse input
class Input
{
public:
	// TODO new function that only sends signal when key is pressed
	static bool GetKeyDown(SDL_Scancode scanCode);
	static void Update();
};

#endif
