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

	void SetScale(int x, int y) { scale.X = x; scale.Y = y; }
	void SetPosition(int x, int y) { position.X = x; position.Y = y; }
	inline void Translate(Vector2D moveVector) { position.X += moveVector.X; position.Y += moveVector.Y; }

private:
	Vector2D position;
	Vector2D scale;
	float rotation;
};