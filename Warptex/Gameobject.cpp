// Includes:
#include "Gameobject.h"

// Empty Constructor
GameObject::GameObject() {
	sprite == nullptr;
	renderer == nullptr;
	scene == nullptr;
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
	// Highly inefficient at high entity counts, will
	// switch to local groups for collision checking in future.
	if (scene != nullptr) {
		collision->UpdateCollisions(scene->GetAllGameObjects());
	}
}

bool GameObject::IsOutOfBounds() {
	if (scene == nullptr) return false;
	if (transform == nullptr) return false;
	SDL_Surface* surface = SDL_GetWindowSurface(scene->GetWindow());
	return (transform->position.X > surface->w || transform->position.Y > surface->h);
}