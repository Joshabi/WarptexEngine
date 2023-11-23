#include "Collision.h"

bool Collision::CheckAABBCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    return SDL_HasIntersection(&rectA, &rectB);
}

bool Collision::CheckAABBCollision(const ColliderComponent& colA, const ColliderComponent& colB) {
    return CheckAABBCollision(colA.collider, colB.collider);
}

bool Collision::CheckSATCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    // Your implementation here
    return false;
}
