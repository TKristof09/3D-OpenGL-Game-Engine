#include "Input.h"
#include "SDL_Backend.h"

bool Input::GetKeyDown(SDL_Scancode scanCode)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
    return state[scanCode];
}

void Input::Update()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			SDLRequestClose(true);
		}

		if(GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			SDLRequestClose(true);
		}
		/*if (e.type == SDL_MOUSEMOTION)
		{
		m_input.SetMouseX(e.motion.x);
		m_input.SetMouseY(e.motion.y);
		}

		if (e.type == SDL_KEYDOWN)
		{
		int value = e.key.keysym.scancode;

		m_input.SetKey(value, true);
		m_input.SetKeyDown(value, true);
		}
		if (e.type == SDL_KEYUP)
		{
		int value = e.key.keysym.scancode;

		m_input.SetKey(value, false);
		m_input.SetKeyUp(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
		int value = e.button.button;

		m_input.SetMouse(value, true);
		m_input.SetMouseDown(value, true);
		}
		if (e.type == SDL_MOUSEBUTTONUP)
		{
		int value = e.button.button;

		m_input.SetMouse(value, false);
		m_input.SetMouseUp(value, true);
		}*/
	}
}
