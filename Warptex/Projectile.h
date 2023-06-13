#pragma once

// Includes:
#include "Gameobject.h"

class Projectile : public GameObject {
public:
	Projectile(Scene* scene, float xVel, float yVel, float speed = 1.0f, float accelRate = 0.0f);
	~Projectile();

	void Update();
	void Collision();
	void HandleMovement();

protected:
	bool bounce = false;  // Should it bounce off arena edges?
	float speed;          // Movement Speed;
	float accelRate;      // The rate at which the projectile slows down or speeds up over time;
};