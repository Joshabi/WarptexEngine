#pragma once

// Includes:
#include <vector>
#include "Gameobject.h"

// Forward References
class GameObject;

class CollisionHandler {
public:
	CollisionHandler(GameObject* parent);
	std::vector<GameObject*> GetCollisions();
	
	template<typename T>
	std::vector<T*> GetCollisionsOfType();

	void UpdateCollisions(std::vector<GameObject*> objectsToCheck);

private:
	std::vector<GameObject*> currentCollisions;
	GameObject* parentObject;
};