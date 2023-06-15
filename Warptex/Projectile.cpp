#pragma once

// Includes
#include "Projectile.h"
#include "Logger.h"

Projectile::Projectile(Scene* scene, int xPos, int yPos, float xVel, float yVel, float speed, float accelRate) : GameObject(scene, 1) {
	transform->SetVelocity(xVel, yVel);
	transform->SetPosition(xPos, yPos);
	sprite->SetPosition(transform->position);
	sprite->Resize(12, 12);
	objectTag = Tag::ENEMY_PROJ;
	colLayer = CollisionLayer::PROJECTILE;
	this->topMoveSpeed = speed;
	this->accelRate = accelRate;
}

Projectile::~Projectile() {
	GameObject::~GameObject();
}

void Projectile::Update() {
	// Handle Movement
	HandleMovement();

	// Handle Collisions
	Collision();

	// Update SpritePosition
	sprite->SetPosition(transform->position);

	// Out of bounds check, if so delete
	if (IsOutOfBounds()) { delete this; }
}

void Projectile::Collision() {
	// Implement Bouncing Here:
	GameObject::Collision();

	// Based on current collisions, do:
	std::vector<GameObject*> collisions = collision->GetCollisionsOfType<GameObject>();
	for (int j = 0; j < collisions.size(); j++) {
		switch (collisions[j]->GetTag()) {
		case Tag::PLAYER:
			// What to do when hit by enemy proj
			Logger::Info("Projectile %i collided with player", this);
			break;
		}
	}
}

void Projectile::HandleMovement() {
	// If we are using acceleration on this projectile else just set speed = top speed
	if (accelRate > 0) {
		moveSpeed += accelRate / 60;
	}
	else {
		moveSpeed = topMoveSpeed;
	}

	transform->Translate(Vector2D(transform->velocity.X * moveSpeed, transform->velocity.Y * moveSpeed));
}