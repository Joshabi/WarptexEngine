#pragma once

/// <summary>
/// Represents a 2D coordinate in space
/// </summary>
class Vector2D {
public:
	float X, Y;

	Vector2D() { Zero(); }
	Vector2D(float initX, float initY) { X = initX; Y = initY; }

	// Allows +Operation between 2 vectors
	inline Vector2D operator+(const Vector2D& vector) const {
		return Vector2D(X + vector.X, Y + vector.Y);
	}

	// Allows -Operation between 2 vectors
	inline Vector2D operator-(const Vector2D& vector) const {
		return Vector2D(X - vector.X, Y - vector.Y);
	}

	// Allows *Operation between 2 vectors
	inline Vector2D operator*(const Vector2D& vector) const {
		return Vector2D(X * vector.X, Y * vector.Y);
	}

	// Allows /Operation between 2 vectors
	inline Vector2D operator/(const Vector2D& vector) const {
		return Vector2D(X / vector.X, Y / vector.Y);
	}

	/// <summary>
	/// Resets a vector to naught
	/// </summary>
	void Zero() { X = 0; Y = 0; }
};