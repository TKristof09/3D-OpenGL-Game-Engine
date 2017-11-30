#ifndef INPUT_H
#define INPUT_H

#include <SDL2\SDL.h>

// TODO mouse input
class Input
{
public:
	// TODO new function that only sends signal when key is pressed
	static bool GetKeyDown(SDL_Scancode scanCode)
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[scanCode])
			return true;
		else
			return false;
	}
};

#endif