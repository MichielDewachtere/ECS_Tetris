#include "BaseSystem.h"

#include "Registry.h"

monthly::BaseSystem::BaseSystem(Registry& registry, uint8_t orderIdx)
	: m_pRegistry(&registry)
	, m_OrderIdx(orderIdx)
{
}