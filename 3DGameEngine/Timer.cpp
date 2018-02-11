#include "Timer.h"
#include "SDL2\SDL.h"


Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void Timer::Start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void Timer::Pause()
{
	if (started && !paused)
	{
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::UnPause()
{
	if (paused)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

int Timer::GetTicks()
{
	if (started)
	{
		if (paused)
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;
		}
	}
	return 0;
}

Timer::~Timer()
{

}
