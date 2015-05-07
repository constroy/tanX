#include <SDL/SDL.h>
#include "timer.hpp"

Timer::Timer()
{
	startTicks=pausedTicks=0;
	started=paused=false;
}
void Timer::Start()
{
	started=true;
	paused=false;
	startTicks=SDL_GetTicks();
}
void Timer::Stop()
{
	started=paused=false;
}
void Timer::Pause()
{
	if (started && !paused)
	{
		paused=true;
		pausedTicks=SDL_GetTicks()-startTicks;
	}
}
void Timer::Unpause()
{
	if (paused)
	{
		paused=false;
		startTicks=SDL_GetTicks()-pausedTicks;
		pausedTicks=0;
	}
}
int Timer::GetTicks()
{
	if (started)
	{
		return paused?pausedTicks:SDL_GetTicks()-startTicks;
	}
	else return 0;
}
bool Timer::IsStarted()
{
	return started;
}
bool Timer::IsPaused()
{
	return paused;
}
