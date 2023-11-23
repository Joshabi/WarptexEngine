#pragma once

#include "SDL.h"
#include "GCS.h"
#include "Components.h"
#include <vector>
#include <algorithm>

class ColliderComponent;  // Forward declaration

class Collision {
public:
    // AABB Collision using built-in SDL_HasIntersection
    static bool CheckAABBCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);

    // AABB Collision using collision components
    static bool CheckAABBCollision(const ColliderComponent& colA, const ColliderComponent& colB);

    // Eventually implement Separating Axis Theorem collision detection
    static bool CheckSATCollision(const SDL_Rect& rectA, const SDL_Rect& rectB);
};
