// Includes:
#include "CollisionHandler.h"
#include "Gameobject.h"

// Constructor
CollisionHandler::CollisionHandler(GameObject* parent) {
	parentObject = parent;
}

CollisionHandler::~CollisionHandler() {

}

// Returns all current collisions
std::vector<GameObject*> CollisionHandler::GetCollisions() { return currentCollisions; }

// Updates list of current collisions given objects to check
void CollisionHandler::UpdateCollisions(std::vector<GameObject*> objectsToCheck) {

	// Erase any current collisions that are no longer being checked, this will remove
	// collisions for entities that no longer exist, aka deleted or no longer being checked
	currentCollisions.erase(
		std::remove_if(
			currentCollisions.begin(), currentCollisions.end(),
			[&](GameObject* obj) {
				return std::find(objectsToCheck.begin(), objectsToCheck.end(), obj) == objectsToCheck.end();
			}
		),
		currentCollisions.end()
				);
	
	// For every object to check, perform an SDL_Intersection, then Add or Remove to currentCollisions
	// as is appropriate based on the result.
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