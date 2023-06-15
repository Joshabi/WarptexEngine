#pragma once

// Includes:
#include "Sprite.h"
#include "EngineScene.h"
#include "Transform.h"
#include "CollisionHandler.h"

// Gameobject Tags
enum class Tag {
	DEFAULT = 0,
	PLAYER = 1,
	OBSTACLE = 2,
	ENEMY = 3,
	FRIENDLY_PROJ = 4,
	ENEMY_PROJ = 5,
	COLLECTIBLE = 6
};

// Gameobject Collision Layers
enum class CollisionLayer {
	DEFAULT = 0,
	PLAYER = 1,
	ENEMY = 2,
	PROJECTILE = 3,
	OBSTACLE = 4
};

// Requires Scene Compiled
class Scene;
class CollisionHandler;

class GameObject {
public:
	GameObject();
	GameObject(Scene* scene, std::string texturePath);
	GameObject(Scene* scene, int texID);
	~GameObject();

	virtual void Input(int key, bool isPressed);
	virtual void Update();
	virtual void Render();
	virtual void Collision();

	Sprite& GetSprite() { return *sprite; }
	Transform& GetTransform() { return *transform; }
	Tag GetTag() { return objectTag; }
	void SetTag(Tag tag) { objectTag = tag; }
	CollisionLayer GetColLayer() { return colLayer; }
	bool IsOutOfBounds();

protected:
	SDL_Renderer* renderer;
	Scene* scene;

	// Generic Component Aspects
	Tag objectTag = Tag::DEFAULT;
	CollisionLayer colLayer = CollisionLayer::DEFAULT;
	Sprite* sprite;
	Transform* transform;
	CollisionHandler* collision;
};