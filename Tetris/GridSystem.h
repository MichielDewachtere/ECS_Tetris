#ifndef TETRIS_GRIDSYSTEM_H
#define TETRIS_GRIDSYSTEM_H

#include <vector>

#include "BaseComponent.h"
#include "BaseSystem.h"

class GridSystem final : public monthly::BaseSystem
{
public:
	GridSystem(monthly::Registry& registry, uint8_t orderIdx)
		: BaseSystem(registry, orderIdx) {}

	void Update() override {}
};

#endif // TETRIS_GRIDSYSTEM_H