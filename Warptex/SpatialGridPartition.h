#pragma once

#include <vector>

class GameObject;

struct GridCell {
	std::vector<GameObject*> objects;
};

class SpatialGridPartition {
private:
	int cellColumns;
	int cellRows;
	std::vector<GridCell> grid;
public:
	SpatialGridPartition(int width, int height);

	void Clear();
	void Update(std::vector<GameObject*> objects);
	void GetPotentialColliders(GameObject* object, std::vector<GameObject*>& potentialColliders);
	void AddPotentialColliders(int cellX, int cellY, std::vector<GameObject*>& potentialColliders);
};