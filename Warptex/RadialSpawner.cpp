// Includes:
#include "RadialSpawner.h"
#include "Projectile.h"
#include "Logger.h"
#include "AudioHandler.h"

RadialSpawner::RadialSpawner(Scene* scene, int initX, int initY) : GameObject(scene, "./Assets/Artwork/Player.png") {
	//Logger::Info("RadialSpawner Created at: x%i y%i", initX, initY);
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
						float streamAngle = currentAngle + (splitID * currentPattern.splitStreamAngleSpread);

						// Clamp
						if (currentAngle > 360) currentAngle -= 360;

						if (reversing) currentAngle = 360 - currentAngle;

						// Convert the angle to radians.
						double radians = currentAngle * M_PI / 180.0;

						// Get Velocity Vector
						float x = static_cast<float>(cos(radians));
						float y = static_cast<float>(sin(radians));

						int posX = transform->position.X;
						int posY = transform->position.Y;

						// Make a new projectile
						Projectile* proj = new Projectile(scene, posX, posY, x, y, currentPattern.projSpeed, currentPattern.projAccel);
						scene->RegisterGameObject(proj);

						// Play Sound Effect Later
						currentAngle += streamAngle;
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
	if (active) { RunActivePattern(); }
}