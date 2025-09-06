#include "Registry.h"

#include <algorithm>

monthly::Registry::Registry()
{
	m_ComponentMap.reserve(ENTITY_AMOUNT);
}

void monthly::Registry::Init()
{
	std::sort(m_Systems.begin(), m_Systems.end(), [](const BaseSystem* a, const BaseSystem* b) -> bool {return a->GetOrderIndex() < b->GetOrderIndex(); });
	std::sort(m_GraphicsSystems.begin(), m_GraphicsSystems.end(), [](const GraphicsSystem* a, const GraphicsSystem* b) -> bool {return a->GetOrderIndex() < b->GetOrderIndex(); });
}

void monthly::Registry::Update()
{
	for (auto& system : m_Systems)
	{
		system->Update();
	}

	for (auto& system : m_GraphicsSystems)
	{
		system->Update();
	}
}

void monthly::Registry::Render()
{
	for (auto& system : m_GraphicsSystems)
	{
		system->Render();
	}
}
