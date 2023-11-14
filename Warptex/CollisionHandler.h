#pragma once

// Includes:
#include <vector>
#include "Gameobject.h"

// Forward References
class GameObject;

/// <summary>
/// Handles collisions between the parent object and other objects
/// </summary>
class CollisionHandler {
public:
	CollisionHandler(GameObject* parent);
	~CollisionHandler();
	std::vector<GameObject*> GetCollisions();
	
	/// <summary>
	/// Returns all collisions where the colliding object is of type T
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns></returns>
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