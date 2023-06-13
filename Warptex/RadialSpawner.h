#pragma once

// ********************************************************* //
//  Radial spawner that uses a pattern to spawn projectiles  //
// ********************************************************* //

// Includes:
#include "Gameobject.h"
#include "RadialPattern.h"

class RadialSpawner : public GameObject {
public:
	RadialSpawner(Scene* scene, int initX, int initY);

	void RunActivePattern();
	void ChangePattern(RadialPattern pattern);

	void Update();
	bool Active() { return active; }
	void SetActive(bool state) { active = state; }
	RadialPattern GetNextPattern() { if (patternQueue.size() != 0) return patternQueue[0]; }

protected:
	Timer internalTimer;
	RadialPattern currentPattern;
	std::vector<RadialPattern> patternQueue = std::vector<RadialPattern>();

	float amountFired = 0;
	float iterationsPassed = 0;
	bool reversing = false;
	bool active = false;
};