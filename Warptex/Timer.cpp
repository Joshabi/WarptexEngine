
// Includes:
#include "Timer.h"

// Reset startTicks on creation
Timer::Timer()
{
	startTicks = 0;
}

// Get current tick count from SDL
void Timer::Reset() {
	startTicks = SDL_GetTicks();
}

// Retrieves how many ticks have passed since this timer started
int Timer::TicksElapsed() {
	return (SDL_GetTicks() - startTicks);
}