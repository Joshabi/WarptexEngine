#pragma once

// Includes:
#include "GCS.h"
#include "Components.h"
#include "Vector2D.h"

/// <summary>
/// Represents a component that can be attached to an entity that handles the position, velocity, scale and rotation of the entity.
/// </summary>
class TransformComponent : public Component {
public:
	// Initialisation
	void Init() override {
		position = Vector2D(0, 0);
		velocity = Vector2D(0, 0);
		scale = Vector2D(0, 0);
		rotation = 0;
	}

	// Main loop overrides:
	void Update() override { }
	void Render(SDL_Renderer* renderer) override { }
	void Input() override { }

	// Setters
	void SetScale(float x, float y) { scale.X = x; scale.Y = y; }
	void SetPosition(float x, float y) { position.X = x; position.Y = y; }
	void SetVelocity(float x, float y) { velocity.X = x; velocity.Y = y; }
	inline void Translate(Vector2D moveVector) { position.X += moveVector.X; position.Y += moveVector.Y; }
	inline void Rotate(float angle) { rotation += angle; }

	// Getters
	Vector2D GetPosition() { return position; }
	Vector2D GetVelocity() { return velocity; }
	Vector2D GetScale() { return scale; }
	float GetRotation() { return rotation; }

protected:
	Vector2D position;
	Vector2D velocity;
	Vector2D scale;
	float rotation;
};