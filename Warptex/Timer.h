#pragma once

// ******************************** //
//  A tick based timer, expand to   //
//  support event scheduling later  //
// ******************************** //

// Includes:
#include <iostream>
#include "SDL.h"

/// <summary>
/// Timer class, used to measure time in ticks
/// </summary>
class Timer {
public:
	Timer();
	void Reset();
	int TicksElapsed();
private:
	int startTicks;
};