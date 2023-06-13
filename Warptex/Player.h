#pragma once

// Includes:
#include "Gameobject.h"

class Player : public GameObject {
public:
	Player(Scene* scene, int initX = 0, int initY = 0);
	~Player();

	int GetLives() { return lives; }

	void Input(int key, bool isPressed);
	void Update();
	void Collision();
	void HandleMovement();

private:
	bool dead;
	int lives;
	float moveSpeed = 3.5f;

	bool MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN; // Movement Input States
};