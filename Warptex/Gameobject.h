#pragma once

// Includes:
#include "Sprite.h"
#include "EngineScene.h"
#include "Transform.h"
#include "CollisionHandler.h"

/// <summary>
/// GameObject Tags
/// </summary>
enum class Tag {
	DEFAULT = 0,
	PLAYER = 1,
	OBSTACLE = 2,
	ENEMY = 3,
	FRIENDLY_PROJ = 4,
	ENEMY_PROJ = 5,
	COLLECTIBLE = 6
};

/// <summary>
/// GameObject Collision Layers
/// </summary>
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

/// <summary>
/// An object consisting of a sprite, transform, and collision handler to be updated in the scene
/// </summary>
class GameObject {
public:
	GameObject(Scene* scene);
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
	void SetActive(bool state) { isActive = state; }
	bool IsActive() { return isActive; }
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
	bool isActive;
};