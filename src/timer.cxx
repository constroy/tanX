#include "timer.hxx"

Timer::Timer() {
	s_ticks = p_ticks = 0;
	started = paused = false;
}
void Timer::Start() {
	started = true;
	paused = false;
	s_ticks = SDL_GetTicks();
}
void Timer::Stop() {
	started = paused = false;
}
void Timer::Pause() {
	if (started && !paused) {
		paused = true;
		p_ticks = SDL_GetTicks() - s_ticks;
	}
}
void Timer::Unpause() {
	if (paused) {
		paused = false;
		s_ticks = SDL_GetTicks() - p_ticks;
		p_ticks = 0;
	}
}
