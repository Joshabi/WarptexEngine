#include "ColliderComponent.h"

CollisionContext::CollisionContext(ColliderComponent* parent) {
    parentCollider = parent;
}

CollisionContext::~CollisionContext() {

}

std::vector<GObject*> CollisionContext::GetCollisions() {
    return currentCollisions;
}

template<typename T>
std::vector<T*> CollisionContext::GetCollisionsOfType() {
    std::vector<T*> collisions;
    return collisions;
}

void CollisionContext::UpdateCollisions(std::vector<GObject*> objectsToCheck) {

}

ColliderComponent::ColliderComponent(CollisionLayer colLayer) {
    this->colLayer = colLayer;
    Init();
}

ColliderComponent::~ColliderComponent() {

}

void ColliderComponent::Init() {

}

void ColliderComponent::Update() {

}

void ColliderComponent::UpdateCollisions(std::vector<GObject*> objectsToCheck) {
    colContext->UpdateCollisions(objectsToCheck);
}
