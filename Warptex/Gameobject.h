#pragma once

// Includes:
#include "Sprite.h"
#include "EngineScene.h"
#include "Transform.h"

// Requires Scene Compiled
class Scene;

class GameObject {
public:
	GameObject();
	GameObject(Scene* scene, std::string texturePath);
	~GameObject();

	virtual void Input(int key, bool isPressed);
	virtual void Update();
	virtual void Render();

	Sprite& GetSprite() { return *sprite; }
	Transform& GetTransform() { return *transform; }
protected:
	SDL_Renderer* renderer;
	Scene* scene;

	// Generic Component Aspects
	Sprite* sprite;
	Transform* transform;
};