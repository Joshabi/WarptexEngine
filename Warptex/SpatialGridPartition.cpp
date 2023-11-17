
// Includes:
#include "SpatialGridPartition.h"
#include "Gameobject.h"

SpatialGridPartition::SpatialGridPartition(int width, int height) : cellColumns(width), cellRows(height) {
	grid.resize(cellColumns * cellRows);
}

/// <summary>
/// Clears this grid
/// </summary>
void SpatialGridPartition::Clear() {
	for (auto& cell : grid) {
		cell.objects.clear();
	}
}

/// <summary>
/// Updates the list of objects in the grids
/// </summary>
/// <param name="objects"></param>
void SpatialGridPartition::Update(std::vector<GameObject*> objects) {
	Clear();
	for (auto& object : objects) {
		int cellX = static_cast<int>(object->GetTransform().position.X / (cellColumns /2));
		int cellY = static_cast<int>(object->GetTransform().position.Y / (cellRows / 2));

		cellX = std::max(0, std::min(cellX, cellColumns - 1));
		cellY = std::max(0, std::min(cellY, cellRows - 1));

		int index = cellY * cellColumns + cellX;
		grid[index].objects.push_back(object);
	}
}

void SpatialGridPartition::AddPotentialColliders(int cellX, int cellY, std::vector<GameObject*>& potentialColliders) {
	if (cellX >= 0 && cellX < cellColumns && cellY >= 0 && cellY < cellRows) {
		int index = cellY * cellColumns + cellX;
		potentialColliders.insert(potentialColliders.end(), grid[index].objects.begin(), grid[index].objects.end());
	}
}

void SpatialGridPartition::GetPotentialColliders(GameObject* object, std::vector<GameObject*>& potentialColliders) {
	int cellX = static_cast<int>(object->GetTransform().position.X / (cellColumns / 2));
	int cellY = static_cast<int>(object->GetTransform().position.Y / (cellRows / 2));

	cellX = std::max(0, std::min(cellX, cellColumns - 1));
	cellY = std::max(0, std::min(cellY, cellRows - 1));

	AddPotentialColliders(cellX, cellY, potentialColliders);
	AddPotentialColliders(cellX - 1, cellY, potentialColliders);
	AddPotentialColliders(cellX + 1, cellY, potentialColliders);
	AddPotentialColliders(cellX, cellY + 1, potentialColliders);
	AddPotentialColliders(cellX, cellY - 1, potentialColliders);
	AddPotentialColliders(cellX - 1, cellY - 1, potentialColliders);
	AddPotentialColliders(cellX + 1, cellY + 1, potentialColliders);
	AddPotentialColliders(cellX - 1, cellY + 1, potentialColliders);
	AddPotentialColliders(cellX + 1, cellY - 1, potentialColliders);
}