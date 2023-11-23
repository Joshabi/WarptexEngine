#pragma once

#include <string>
#include <vector>
#include "GCS.h"
#include "Components.h"
#include "Collision.h"
#include "SDL.h"

class TransformComponent;  // Forward declaration

enum class CollisionLayer {
    DEFAULT = 0,
    PLAYER = 1,
    ENEMY = 2,
    PROJECTILE = 3,
    OBSTACLE = 4
};

/// <summary>
/// Context pertaining to the current collisions of a collider
/// </summary>
class CollisionContext {
public:
    CollisionContext(class ColliderComponent* parent) { parentCollider = parent; }
    ~CollisionContext() { }

    std::vector<GObject*> GetCollisions() { return currentCollisions; }

    template<typename T>
    std::vector<T*> GetCollisionsOfType() {
        std::vector<T*> collisions;
        return collisions;
    }

    void UpdateCollisions(std::vector<GObject*> objectsToCheck) { }

private:
    std::vector<GObject*> currentCollisions;
    class ColliderComponent* parentCollider;
};

/// <summary>
/// Handles collisions for its parent GameObject, representing a hitbox
/// </summary>
class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    CollisionLayer colLayer;

    ColliderComponent(CollisionLayer colLayer) {
        this->colLayer = colLayer;
        Init();
    }
    ~ColliderComponent() { }

    void Init() override { }
    void Update() override { }
    void UpdateCollisions(std::vector<GObject*> objectsToCheck) {
        colContext->UpdateCollisions(objectsToCheck);
    }

private:
    TransformComponent* transform;
    CollisionContext* colContext;
};
