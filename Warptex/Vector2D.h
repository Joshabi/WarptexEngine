#pragma once

class Vector2D {
public:
	Vector2D() { Zero(); }
	Vector2D(int initX, int initY) { X = initX; Y = initY; }

	// Allows +Operation between 2 vectors
	inline Vector2D operator+(const Vector2D& vector) const {
		return Vector2D(X + vector.X, Y + vector.Y);
	}

	// Allows -Operation between 2 vectors
	inline Vector2D operator-(const Vector2D& vector) const {
		return Vector2D(X - vector.X, Y - vector.Y);
	}

	// Reset to 0 the X and Y
	void Zero() { X = 0; Y = 0; }
	int X, Y;
};