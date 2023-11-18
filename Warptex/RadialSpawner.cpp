// Includes:
#include "RadialSpawner.h"
#include "Projectile.h"
#include "Logger.h"
#include "AudioHandler.h"

RadialSpawner::RadialSpawner(Scene* scene, int initX, int initY) : GameObject(scene, 0),
projPool(10, scene) {
	Logger::Info("RadialSpawner Created at: x%i y%i", initX, initY);
	transform->SetPosition(initX, initY);
	sprite->SetPosition(transform->position);
	objectTag = Tag::ENEMY;
}

// Runs active pattern
void RadialSpawner::RunActivePattern() {
	float angleIncrement = (currentPattern.spawnStreamAngleSpread == 0) ?
		360.0f / currentPattern.spawnStreamCount :
		currentPattern.spawnStreamAngleSpread;

	if (currentPattern.spawnerSpinReverse) reversing = true;
	float currentRotation = currentPattern.startRotation;

	// If iterations are left
	if (iterationsPassed < currentPattern.iterations) {

		if (amountFired <= currentPattern.projectileCount) {

			// If time to fire:
			if (internalTimer.TicksElapsed() > currentPattern.projFireRate * 60 * 16.6666f) {

				currentRotation += currentPattern.spawnerSpinAngleChange * amountFired;

				// Get the stream points
				for (int streamID = 0; streamID < currentPattern.spawnStreamCount; streamID++) {
					float currentAngle = currentRotation + (streamID * angleIncrement);

					// Get the projectile spawn points
					for (int splitID = 0; splitID < currentPattern.splitStreamCount; splitID++) {
						float streamAngle = currentAngle + (splitID - currentPattern.splitStreamCount / 2.0f) * currentPattern.splitStreamAngleSpread;

						// Clamp
						streamAngle = fmod(streamAngle, 360.0f);

						if (reversing) streamAngle = 360 - streamAngle;

						// Convert the angle to radians.
						double radians = streamAngle * M_PI / 180.0;

						// Get Velocity Vector
						float x = static_cast<float>(cos(radians));
						float y = static_cast<float>(sin(radians));

						int posX = transform->position.X;
						int posY = transform->position.Y;

						// Make a new projectile
						Projectile* proj = projPool.GetObject();
						proj->Initialize(posX, posY, x, y, currentPattern.projSpeed, currentPattern.projAccel);

						// Play Sound Effect Later
					}
				}
				AudioHandler::Inst().PlaySound(0);
				amountFired += 1;
				internalTimer.Reset();
			}
		}
		else {
			amountFired = 0;
			iterationsPassed += 1;
			if (currentPattern.flipEveryIteration) { reversing = !reversing; }
		}
	}
	else {
		SetActive(false);
	}
}

void RadialSpawner::ChangePattern(RadialPattern pattern) {
	srand(time(0));
	currentPattern = pattern;
	amountFired = 0;
	iterationsPassed = 0;
}

void RadialSpawner::Update() {
	CleanupInactiveProjectiles();
	if (active) { RunActivePattern(); }
}