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
	Transform() {}
	~Transform() {}

	Vector2D position = Vector2D(0,0);
	Vector2D velocity = Vector2D(0, 0);
	Vector2D scale = Vector2D(0, 0);
	float rotation = 0;

	void SetScale(int x, int y) { scale.X = x; scale.Y = y; }
	void SetPosition(int x, int y) { position.X = x; position.Y = y; }
	void SetVelocity(int x, int y) { velocity.X = x; velocity.Y = y; }
	inline void Translate(Vector2D moveVector) { position.X += moveVector.X; position.Y += moveVector.Y; }
};