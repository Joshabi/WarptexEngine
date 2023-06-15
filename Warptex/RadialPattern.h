#pragma once

// *************************************************** //
//  Pattern for a Radial Projectile Spawner.           //
// *************************************************** //

// Includes:
#include <string>
#include <sstream>

class RadialPattern {
public:
	RadialPattern() {}

	float iterations = 3;               // How many times to repeat this pattern
	int spawnStreamCount = 5;          // How many spawn streams around the circle
	float spawnStreamAngleSpread = 0; // Angle between spawn streams
	int splitStreamCount = 1;          // How many projectile streams per spawn stream
	float splitStreamAngleSpread = 0;  // Angle between projectile streams
	int projectileCount = 25;          // How many projectiles to spawn per stream

	float startRotation = 0;           // Starting rotation for RadialSpawner
	float spawnerSpinAngleChange = 12.5f;  // Speed at which it rotates
	bool spawnerSpinReverse = false;    // Spin in reverse?
	bool flipEveryIteration = true;   // Spin in opposite direction each iteration
	float projFireRate = 0.5f;         // Rate to fire projectiles
	float projSpeed = 2;               // Speed of projectiles
	float projLifetime = 0;            // Lifetime of projectiles (only relevant for those not leaving screen "bouncing")
	bool tethered = false;             // Projectiles positionally tethered to the spawn object?
};