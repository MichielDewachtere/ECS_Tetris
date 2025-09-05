#ifndef TETRISENGINE_REGISTRY_H
#define TETRISENGINE_REGISTRY_H

#include <typeindex>
#include <unordered_map>
#include <map>
#include <bitset>
#include <memory>
#include <set>

#include "EngineConcepts.h"
#include "Entity.h"

#define COMPONENT_AMOUNT 64
#define ENTITY_AMOUNT 512

namespace monthly
{
	class Registry final
	{
	public:
		Registry();

		void Init();
		void Update();

		template<derived_from_component... TComponents>
		entity_id RegisterEntity(TComponents&&... components);

		template<derived_from_component T>
		void RegisterComponent() const;
		//template<derived_from_service T>
		void RegisterSystem(const BaseSystem& system);

		template<derived_from_component T>
		void AddComponent(entity_id entity, T component);

	private:
		// System Variables
		std::vector<BaseSystem> m_Systems{};

		// Component Variables
		std::vector<std::bitset<COMPONENT_AMOUNT>> m_ComponentMap{};
		std::unordered_map<std::type_index, uint32_t> m_ComponentsToIndex{};

		std::unordered_map<std::type_index, std::unique_ptr<std::vector<BaseComponent>>> m_SparseMaps{};
		std::unordered_map<std::type_index, std::unique_ptr<std::vector<entity_id>>> m_DenseMaps{};

		template<derived_from_component TComponent>
		void StoreComponent(entity_id entity, TComponent&& component);

		static inline entity_id m_CurrentComponentIdx = 0;
	};

	template <derived_from_component... TComponents>
	entity_id Registry::RegisterEntity(TComponents&&... components)
	{
		std::bitset<COMPONENT_AMOUNT> componentMap{};
		m_ComponentMap.push_back(componentMap);

		entity_id entity = CreateNewEntity();

		(RegisterComponent<TComponents>(), ...);
		(StoreComponent(entity, std::forward<TComponents>(components)), ...);

		return entity;
	}

	template <derived_from_component T>
	void Registry::RegisterComponent() const
	{
		if (!m_SparseMaps.contains(typeid(T)))
		{
			m_ComponentsToIndex[typeid(T)] = m_CurrentComponentIdx++;

			m_SparseMaps[typeid(T)] = std::unique_ptr(std::vector<T>(ENTITY_AMOUNT));
			m_DenseMaps[typeid(T)] = std::unique_ptr<std::vector<entity_id>>();
		}
	}

	template <derived_from_component T>
	void Registry::AddComponent(entity_id entity, T component)
	{

	}

	template <derived_from_component TComponent>
	void Registry::StoreComponent(entity_id entity,TComponent&& component)
	{
		auto& type = typeid(TComponent);

		if (m_DenseMaps[type])

		m_SparseMaps[type].get()[entity] = std::forward<TComponent>(component);
		m_DenseMaps[type].get()->push_back(entity);

		m_ComponentMap[entity].flip(m_ComponentsToIndex[type]);
	}
}

#endif // TETRISENGINE_REGISTRY_H
