#pragma once

// Includes:
#include "SDL.h"
#include <vector>
#include <algorithm>

static class Collision {
public:
	// AABB Collision using built-in SDL_HasIntersection
	static bool CheckAABBCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
		return SDL_HasIntersection(&rectA, &rectB);
	}
	
	// Eventually implement Seperating Axis Theorem collision detection
	static bool CheckSATCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) { }
};