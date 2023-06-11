// Includes:
#include "Gameobject.h"

// Empty Constructor
GameObject::GameObject() {
	sprite == nullptr;
	renderer == nullptr;
	scene == nullptr;
}

// Constructor with texture
GameObject::GameObject(Scene* scene, std::string texturePath) {
	this->scene = scene;
	renderer = this->scene->GetRenderer();
	sprite = new Sprite(renderer, texturePath);
}

void GameObject::Input() {
	
}

void GameObject::Update() {

}

void GameObject::Render() {
	if (sprite != nullptr) {
		sprite->Render(renderer);
	}
}