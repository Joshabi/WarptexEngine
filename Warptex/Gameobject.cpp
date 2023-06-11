// Includes:
#include "Gameobject.h"

// Empty Constructor
GameObject::GameObject() {
	sprite == nullptr;
	renderer == nullptr;
	scene == nullptr;
	transform = new Transform();
}

// Constructor with texture
GameObject::GameObject(Scene* scene, std::string texturePath) {
	this->scene = scene;
	renderer = this->scene->GetRenderer();
	sprite = new Sprite(renderer, texturePath);
	transform = new Transform();
}

GameObject::~GameObject() {
	transform->~Transform();
	sprite->~Sprite();
}

void GameObject::Input(int key, bool isPressed) {
	
}

void GameObject::Update() {

}

void GameObject::Render() {
	if (sprite != nullptr) {
		sprite->Render(renderer);
	}
}