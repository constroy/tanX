#ifndef _TIMER_HXX
#define _TIMER_HXX

#include <SDL/SDL.h>

class Timer {
public:
	Timer();
	void Start();
	void Stop();
	void Pause();
	void Unpause();
	int GetTicks()  const {
		if (started) return paused ? p_ticks : SDL_GetTicks() - s_ticks;
		else return 0;
	}
	bool IsStarted() const {
		return started;
	}
	bool IsPaused() const {
		return paused;
	}
private:
	int s_ticks;
	int p_ticks;
	bool paused;
	bool started;
};

#endif
