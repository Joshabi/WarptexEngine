#pragma once

// ********************************************************* //
//  Radial spawner that uses a pattern to spawn projectiles  //
// ********************************************************* //

// Includes:
#include "Gameobject.h"
#include "RadialPattern.h"
#include "ObjectPool.h"
#include "Logger.h"

class RadialSpawner : public GameObject {
public:
	RadialSpawner(Scene* scene, int initX = 0, int initY = 0);

	void RunActivePattern();
	void ChangePattern(RadialPattern pattern);
	void CleanupInactiveProjectiles() {
		std::vector<Projectile*> objectPool = projPool.GetObjectPool();
		for (Projectile* projectile : objectPool) {
			if (!projectile->IsActive()) {
				projPool.ReleaseObject(projectile);
				// Perform any necessary cleanup for the projectile
			}
		}
	}

	void Update();
	bool Active() { return active; }
	void SetActive(bool state) { active = state; }
	RadialPattern GetNextPattern() { if (patternQueue.size() != 0) return patternQueue[0]; }

protected:
	Timer internalTimer;
	RadialPattern currentPattern;
	ObjectPool<Projectile> projPool;
	std::vector<RadialPattern> patternQueue = std::vector<RadialPattern>();

	float amountFired = 0;
	int iterationsPassed = 0;
	bool reversing = false;
	bool active = false;
};