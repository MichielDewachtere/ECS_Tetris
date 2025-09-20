#ifndef TETRIS_COMPONENTS_H
#define TETRIS_COMPONENTS_H

#include <vector>

#include "BaseComponent.h"
#include "Entity.h"

struct EntityComponent : monthly::BaseComponent
{
	monthly::entity_id parent = monthly::invalid_id;
};

struct PositionComponent : monthly::BaseComponent
{
	PositionComponent() = default;
	PositionComponent(int x, int y) : globalX(x), globalY (y) {}

	void SetGlobalX(const int newX) { globalX = newX; isDirty = true; }
	void SetGlobalY(const int newY) { globalY = newY; isDirty = true; }

	int GetGlobalX() const { return globalX; }
	int GetGlobalY() const { return globalY; }
	int GetLocalX() const { return localX; }
	int GetLocalY() const { return localY; }

private:
	friend class TransformSystem;
	int globalX, globalY;
	int localX = 0, localY = 0;
	bool isDirty = true;
};

struct TetrominoComponent : monthly::BaseComponent
{
	bool isControlled;
	std::vector<std::vector<bool>> shape;
};

struct RotationComponent : monthly::BaseComponent
{
	int rot;
};

struct GridComponent : monthly::BaseComponent
{
	std::vector<std::vector<bool>> grid;

};

#endif // TETRIS_COMPONENTS_H