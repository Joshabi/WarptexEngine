#pragma once

// Includes:
#include "Gameobject.h"

class Projectile : public GameObject {
public:
	Projectile(Scene* scene, float xPos, float yPos, float xVel = 0.0f, float yVel = 0.0f, float speed = 1.0f, float accelRate = 1.0f);
	~Projectile();

	void Update();
	void Collision();
	void HandleMovement();

protected:
	bool bounce = false;  // Should it bounce off arena edges?
	float speed;          // Movement Speed;
	float accelRate;      // The rate at which the projectile slows down or speeds up over time;
};