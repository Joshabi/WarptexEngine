#pragma once

// Includes
#include "Projectile.h"
#include "Logger.h"

Projectile::Projectile(Scene* scene) : GameObject(scene, 1) {
	Initialize(0, 0, 0, 0, 0, 0);
	sprite->SetPosition(transform->position);
	sprite->Resize(12, 12);
	objectTag = Tag::ENEMY_PROJ;
	colLayer = CollisionLayer::PROJECTILE;
}

void Projectile::Initialize(int xPos, int yPos, float xVel, float yVel, float speed, float accelRate)
{
	transform->SetVelocity(xVel, yVel);
	transform->SetPosition(xPos, yPos);
	this->accelRate = accelRate;

	moveSpeed = 0.0f;
	topMoveSpeed = 0.0f;

	if (accelRate == 0) {
		moveSpeed = speed;
	}
	else {
		this->topMoveSpeed = speed;
	}

	SetActive(true);
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
	if (IsOutOfBounds()) { 
		SetActive(false); 
		Logger::Debug("Projectile %i out of bounds", this);
	}
}

void Projectile::Collision() {
	// Implement Bouncing Here:
	GameObject::Collision();
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