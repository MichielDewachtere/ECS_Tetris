#include "Registry.h"

#include <algorithm>

monthly::Registry::Registry()
{
	m_ComponentMap.reserve(ENTITY_AMOUNT);
}

void monthly::Registry::Init()
{
	std::sort(m_Systems.begin(), m_Systems.end(), [](const BaseSystem& a, const BaseSystem& b) -> bool {return a.GetOrderIndex() < b.GetOrderIndex(); });
}

void monthly::Registry::Update()
{
	for (auto& system : m_Systems)
	{
		system.Update();
	}
}

void monthly::Registry::RegisterSystem(const BaseSystem& system)
{
	m_Systems.push_back(system);
}