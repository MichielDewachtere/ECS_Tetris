#include "TransformSystem.h"

#include <Registry.h>

#include "Components.h"

TransformSystem::TransformSystem(monthly::Registry& registry)
	: BaseSystem(registry, 0)
{
}

void TransformSystem::Update()
{
	auto idcs = *m_pRegistry->GetDenseMap<PositionComponent>();
	for (monthly::entity_id idx : idcs)
	{
		UpdateLocalPos(idx);
	}
}

void TransformSystem::UpdateLocalPos(monthly::entity_id id)
{
	PositionComponent* pos = m_pRegistry->GetComponent<PositionComponent>(id).value();
	if (pos->isDirty == false)
		return;

	EntityComponent* entity = m_pRegistry->GetComponent<EntityComponent>(id).value();
	if (entity->parent == monthly::invalid_id)
	{
		pos->isDirty = false;
		return;
	}

	PositionComponent* parentPos = m_pRegistry->GetComponent<PositionComponent>(entity->parent).value();
	if (parentPos->isDirty)
	{
		UpdateLocalPos(entity->parent);
	}

	pos->localX = pos->GetGlobalX() - parentPos->GetGlobalX();
	pos->localY = pos->GetGlobalY() - parentPos->GetGlobalY();
	pos->isDirty = false;
}