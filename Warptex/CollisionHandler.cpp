// Includes:
#include "CollisionHandler.h"
#include "Gameobject.h"

// Constructor
CollisionHandler::CollisionHandler(GameObject* parent) {
	parentObject = parent;
}

// Returns all current collisions
std::vector<GameObject*> CollisionHandler::GetCollisions() { return currentCollisions; }

// Updates list of current collisions given objects to check
void CollisionHandler::UpdateCollisions(std::vector<GameObject*> objectsToCheck) {
	for (int i = 0; i < objectsToCheck.size(); i++) {
		SDL_Rect thisRect = parentObject->GetSprite().GetRect();
		SDL_Rect otherRect = objectsToCheck[i]->GetSprite().GetRect();
		bool collision = SDL_HasIntersection(&thisRect, &otherRect);

		if (collision) {
			auto iterator = std::find(currentCollisions.begin(), currentCollisions.end(), objectsToCheck[i]);
			if (iterator == currentCollisions.end()) {
				currentCollisions.push_back(objectsToCheck[i]);
			}
		}
		else {
			auto iterator = std::find(currentCollisions.begin(), currentCollisions.end(), objectsToCheck[i]);
			if (iterator != currentCollisions.end()) {
				currentCollisions.erase(iterator);
			}
		}
	}
}