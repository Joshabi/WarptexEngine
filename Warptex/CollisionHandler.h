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
	

	// Returns all collisions of a type that inherits from GameObject
	template<typename T>
	std::vector<T*> GetCollisionsOfType() {
		std::vector<T*> collisions;
		for (GameObject* obj : currentCollisions) {
			T* castedObj = dynamic_cast<T*>(obj);
			if (castedObj) { collisions.push_back(obj); }
		}
		return collisions;
	}

	void UpdateCollisions(std::vector<GameObject*> objectsToCheck);

private:
	std::vector<GameObject*> currentCollisions;
	GameObject* parentObject;
};