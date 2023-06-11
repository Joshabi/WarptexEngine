#pragma once

// Includes:
#include "Gameobject.h"

class Player : public GameObject {
public:
	Player(Scene* scene);
	~Player();

	int GetLives() { return lives; }

	void Input(int key, bool isPressed);
	void Update();
	void HandleMovement();

private:
	bool dead;
	int lives;
	float moveSpeed = 3.5f;

	bool MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN; // Movement Input States
};