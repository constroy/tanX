#ifndef _TIMER_HXX
#define _TIMER_HXX

class Timer
{
	private:
		int startTicks;
		int pausedTicks;
		bool paused;
		bool started;
	public:
		Timer();
		void Start();
		void Stop();
		void Pause();
		void Unpause();
		int GetTicks();
		bool IsStarted();
		bool IsPaused();
};

#endif
