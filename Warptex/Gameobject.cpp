// Includes:
#include "Gameobject.h"


// Empty Constructor
GameObject::GameObject(Scene* scene) {
	this->scene = scene;
	renderer = this->scene->GetRenderer();
	sprite = new Sprite(renderer, 0);
	transform = new Transform();
	collision = new CollisionHandler(this);
}

// Constructor with texture
GameObject::GameObject(Scene* scene, std::string texturePath) {
	this->scene = scene;
	renderer = this->scene->GetRenderer();
	sprite = new Sprite(renderer, texturePath);
	transform = new Transform();
	collision = new CollisionHandler(this);
}

GameObject::GameObject(Scene* scene, int texID)
{
	this->scene = scene;
	renderer = this->scene->GetRenderer();
	sprite = new Sprite(renderer, texID);
	transform = new Transform();
	collision = new CollisionHandler(this);
}

GameObject::~GameObject() {
	delete transform;
	delete sprite;
	delete collision;
	transform = nullptr;
	sprite = nullptr;
	collision = nullptr;
	scene->DeregisterGameObject(this);
}

void GameObject::Input(int key, bool isPressed) {
	
}

void GameObject::Update() {
	Collision();
}

void GameObject::Render() {
	if (sprite != nullptr) {
		sprite->Render(renderer);
	}
}

void GameObject::Collision() {
	if (scene == nullptr) return;

	std::vector<GameObject*> spatialColliders = scene->GetAllGameObjects();
	scene->GetGrid().GetPotentialColliders(this, spatialColliders);
	spatialColliders.erase(std::remove_if(spatialColliders.begin(), spatialColliders.end(), [&](GameObject* obj) {
		return (obj->colLayer == CollisionLayer::PROJECTILE && this->colLayer == CollisionLayer::PROJECTILE);
		}), spatialColliders.end());

	if (scene != nullptr) {
		collision->UpdateCollisions(spatialColliders);
	}
}

bool GameObject::IsOutOfBounds() {
	if (scene == nullptr || transform == nullptr) {
		return false;
	}

	int windowWidth = scene->GetWindowSurface()->w;
	int windowHeight = scene->GetWindowSurface()->h;

	return (transform->position.X < 0 || transform->position.Y < 0 ||
		transform->position.X >= windowWidth || transform->position.Y >= windowHeight);
}

void GameObject::SetActive(bool state) {
	isActive = state;
}