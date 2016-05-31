#ifndef _TIMER_HXX
#define _TIMER_HXX

#include <SDL/SDL.h>

class Timer
{
	private:
		int s_ticks;
		int p_ticks;
		bool paused;
		bool started;
	public:
		Timer();
		void Start();
		void Stop();
		void Pause();
		void Unpause();
		int GetTicks() const;
		bool IsStarted() const;
		bool IsPaused() const;
};

inline int Timer::GetTicks() const
{
	if (started) return paused?p_ticks:SDL_GetTicks()-s_ticks;
	else return 0;
}
inline bool Timer::IsStarted() const
{
	return started;
}
inline bool Timer::IsPaused() const
{
	return paused;
}

#endif
