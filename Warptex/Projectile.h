#pragma once

// Includes:
#include "Gameobject.h"

/// <summary>
/// A projectile object that can be fired in a given direction
/// </summary>
class Projectile : public GameObject {
public:
	Projectile() = default;
	Projectile(Scene* scene);
	~Projectile();

	void Initialize(int xPos = 0, int yPos = 0, float xVel = 0, float yVel = 0, float speed = 0, float accelRate = 0.0f);
	void Update();
	void Collision();
	void HandleMovement();

protected:
	bool bounce = false;  // Should it bounce off arena edges?
	float topMoveSpeed = 1;  // Top movement speed;
	float moveSpeed = 0;   // Actual movement speed;
	float accelRate;   // The rate at which the projectile slows down or speeds up over time;
};