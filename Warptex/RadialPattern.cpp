#include "nlohmann/json.hpp"
#include "RadialPattern.h"

void from_json(const nlohmann::json& j, RadialPattern& pattern) {
	j.at("iterations").get_to(pattern.iterations);
	j.at("spawnStreamCount").get_to(pattern.spawnStreamCount);
	j.at("spawnStreamAngleSpread").get_to(pattern.spawnStreamAngleSpread);
	j.at("splitStreamCount").get_to(pattern.splitStreamCount);
	j.at("splitStreamAngleSpread").get_to(pattern.splitStreamAngleSpread);
	j.at("projectileCount").get_to(pattern.projectileCount);
	j.at("startRotation").get_to(pattern.startRotation);
	j.at("spawnerSpinAngleChange").get_to(pattern.spawnerSpinAngleChange);
	j.at("spawnerSpinReverse").get_to(pattern.spawnerSpinReverse);
	j.at("flipEveryIteration").get_to(pattern.flipEveryIteration);
	j.at("projFireRate").get_to(pattern.projFireRate);
	j.at("projSpeed").get_to(pattern.projSpeed);
	j.at("projAccel").get_to(pattern.projAccel);
	j.at("projLifetime").get_to(pattern.projLifetime);
	j.at("tethered").get_to(pattern.tethered);
}
