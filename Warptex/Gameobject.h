#pragma once

// Includes:
#include "Sprite.h"
#include "EngineScene.h"
#include "Transform.h"
#include "CollisionHandler.h"

// Gameobject Tags
enum class Tag {
	PLAYER = 0,
	OBSTACLE = 1,
	ENEMY = 2,
	FRIENDLY_PROJ = 3,
	ENEMY_PROJ = 4,
	COLLECTIBLE = 5,
	VOID = 99
};

// Requires Scene Compiled
class Scene;
class CollisionHandler;

class GameObject {
public:
	GameObject();
	GameObject(Scene* scene, std::string texturePath);
	~GameObject();

	virtual void Input(int key, bool isPressed);
	virtual void Update();
	virtual void Render();
	virtual void Collision();

	Sprite& GetSprite() { return *sprite; }
	Transform& GetTransform() { return *transform; }
	Tag GetTag() { return objectTag; }
	void SetTag(Tag tag) { objectTag = tag; }

protected:
	SDL_Renderer* renderer;
	Scene* scene;

	// Generic Component Aspects
	Tag objectTag = Tag::VOID;
	Sprite* sprite;
	Transform* transform;
	CollisionHandler* collision;
};