#pragma once

// *********************************************** //
//  Representation of position and rotation, that  //
//  can have parent or child objects that tie      //
//  the movement together                          //
// *********************************************** //

// Includes:
#include <vector>
#include "SDL.h"
#include "Vector2D.h"
#include "Gameobject.h"

class Transform {
public:
	Transform() {
		position = Vector2D(0, 0);
		velocity = Vector2D(0, 0);
		scale = Vector2D(0, 0);
		rotation = 0;
	}
	~Transform() {}

	Vector2D position;
	Vector2D velocity;
	Vector2D scale;
	float rotation;

	void SetScale(float x, float y) { scale.X = x; scale.Y = y; }
	void SetPosition(float x, float y) { position.X = x; position.Y = y; }
	void SetVelocity(float x, float y) { velocity.X = x; velocity.Y = y; }
	inline void Translate(Vector2D moveVector) { position.X += moveVector.X; position.Y += moveVector.Y; }
};