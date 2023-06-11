#pragma once

// ******************************** //
//  A tick based timer, expand to   //
//  support event scheduling later  //
// ******************************** //

// Includes:
#include <iostream>
#include "SDL.h"

class Timer {
public:
	Timer();
	void Reset();
	int TicksElapsed();
private:
	int startTicks;
};