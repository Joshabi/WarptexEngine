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

class CollisionContext {
public:
    CollisionContext(class ColliderComponent* parent);
    ~CollisionContext();

    std::vector<GObject*> GetCollisions();

    template<typename T>
    std::vector<T*> GetCollisionsOfType();

    void UpdateCollisions(std::vector<GObject*> objectsToCheck);

private:
    std::vector<GObject*> currentCollisions;
    class ColliderComponent* parentCollider;
};

class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    CollisionLayer colLayer;

private:
    TransformComponent* transform;
    CollisionContext* colContext;

public:
    ColliderComponent(CollisionLayer colLayer);
    ~ColliderComponent();

    void Init() override;
    void Update() override;
    void UpdateCollisions(std::vector<GObject*> objectsToCheck);
};
