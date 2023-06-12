// Includes:
#include "Player.h"
#include "Logger.h"

Player::Player(Scene* scene) : GameObject(scene,"./Assets/Artwork/Player.png") {
	Logger::Info("Player Created");
	objectTag = Tag::PLAYER;
	lives = 3;
	dead = false;
}

Player::~Player() {

}

void Player::Input(int key, bool pressed) {
	// Handle inputs for moving
	switch (key) {
	case SDLK_w: { MOVE_UP = pressed; break;  };
	case SDLK_a: { MOVE_LEFT = pressed; break; };
	case SDLK_s: { MOVE_DOWN = pressed; break; };
	case SDLK_d: { MOVE_RIGHT = pressed; break; };
	}
}

void Player::Update() {
	// Move Player
	HandleMovement();

	// Update SpritePosition
	sprite->SetPosition(transform->position);
}

void Player::HandleMovement() {
	// Translate position based on velocity;
	transform->Translate(transform->velocity);

	// For now, reset velocity
	// Will revamp with accel and other stuff later
	transform->SetVelocity(0, 0);

	if (!dead) {
		if (MOVE_LEFT) {
			transform->SetVelocity(transform->velocity.X - 1 * moveSpeed,
				transform->velocity.Y); MOVE_LEFT = false;
		}
		if (MOVE_RIGHT) {
			transform->SetVelocity(transform->velocity.X + 1 * moveSpeed,
				transform->velocity.Y); MOVE_RIGHT = false;
		}
		if (MOVE_UP) {
			transform->SetVelocity(transform->velocity.X,
				transform->velocity.Y - 1 * moveSpeed); MOVE_UP = false;
		}
		if (MOVE_DOWN) {
			transform->SetVelocity(transform->velocity.X,
				transform->velocity.Y + 1 * moveSpeed); MOVE_DOWN = false;
		}
	}
}