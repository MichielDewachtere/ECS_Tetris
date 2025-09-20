#ifndef TETRIS_TRANSFORMSYSTEM_H
#define TETRIS_TRANSFORMSYSTEM_H

#include "BaseSystem.h"
#include "Entity.h"

class TransformSystem final : public monthly::BaseSystem
{
public:
	TransformSystem(monthly::Registry& registry);
	virtual ~TransformSystem() override = default;

	virtual void Update() override;

private:
	void UpdateLocalPos(monthly::entity_id id);
};

#endif // TETRIS_TRANSFORMSYSTEM_H