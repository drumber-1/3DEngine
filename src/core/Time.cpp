#include "Time.hpp"

#include <SDL2/SDL.h>

double Time::getTime() {
	return (double)(SDL_GetTicks()) / 1000.0;
}

void Time::sleep(unsigned int milliseconds) {
	SDL_Delay(milliseconds);
}