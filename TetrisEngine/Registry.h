#ifndef TETRISENGINE_REGISTRY_H
#define TETRISENGINE_REGISTRY_H


#include <bitset>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include <optional>

#include "GraphicsSystem.h"
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
		void Render();

		template<derived_from_component... TComponents>
		entity_id RegisterEntity(TComponents&&... components);

		template<derived_from_component T>
		void RegisterComponent();

		template<derived_from_system T>
		void RegisterSystem(T* system);

		template<derived_from_component T>
		void AddComponent(entity_id entity, T component);
		template<derived_from_component T>
		std::optional<T*> GetComponent(entity_id entity);
		template<derived_from_component T>
		void RemoveComponent(entity_id entity);

		template<derived_from_component T>
		std::vector<entity_id>* GetDenseMap();

		template<derived_from_component T>
		std::vector<T>* GetSparseMap();

	private:
		// System Variables
		std::vector<BaseSystem*> m_Systems{};
		std::vector<GraphicsSystem*> m_GraphicsSystems{};

		// Component Variables
		std::vector<std::bitset<COMPONENT_AMOUNT>> m_ComponentMap{};
		std::unordered_map<std::type_index, uint32_t> m_ComponentsToIndex{};

		std::unordered_map<std::type_index, void*> m_SparseMaps{};
		std::unordered_map<std::type_index, std::vector<entity_id>> m_DenseMaps{};

		template<derived_from_component TComponent>
		void StoreComponent(entity_id entity, TComponent&& component);

		static inline entity_id m_CurrentComponentIdx = 0;
	};

	template <derived_from_component... TComponents>
	entity_id Registry::RegisterEntity(TComponents&&... components)
	{
		std::bitset<COMPONENT_AMOUNT> componentMap{};
		m_ComponentMap.push_back(componentMap);

		entity_id entity = Entity::CreateNewEntity();

		(RegisterComponent<TComponents>(), ...);
		(StoreComponent(entity, std::forward<TComponents>(components)), ...);

		return entity;
	}

	template <derived_from_component T>
	void Registry::RegisterComponent()
	{
		auto& type = typeid(T);
		if (!m_ComponentsToIndex.contains(type))
		{
			m_ComponentsToIndex[type] = m_CurrentComponentIdx++;

			m_SparseMaps[type] = new std::vector<T>(ENTITY_AMOUNT);
			m_DenseMaps[type] = std::vector<entity_id>();
		}
	}

	template <derived_from_system T>
	void Registry::RegisterSystem(T* system)
	{
		if (std::is_base_of_v<GraphicsSystem, T>)
		{
			m_GraphicsSystems.push_back(dynamic_cast<GraphicsSystem*>(system));
		}
		else if (system != nullptr)
		{
			m_Systems.push_back(system);
		}
	}

	template <derived_from_component T>
	void Registry::AddComponent(entity_id entity, T component)
	{
		auto& type = typeid(T);
		auto& bitset = m_ComponentMap[entity];
		if (!m_ComponentsToIndex.contains(type))
		{
			RegisterComponent<T>();
		}
		else if (bitset[m_ComponentsToIndex[type]])
		{
			// TODO: Log warning entity has already component T.
			return;
		}

		bitset.set(m_ComponentsToIndex[type], true);
		// TODO: Check if not already in map
		m_DenseMaps[type].push_back(entity);
		auto& sparseMap = *GetSparseMap<T>();
		sparseMap[entity] = component;
	}

	template <derived_from_component T>
	std::optional<T*> Registry::GetComponent(entity_id entity)
	{
		auto& type = typeid(T);
		if (!m_ComponentsToIndex.contains(type))
		{
			// TODO: Log warning entity has no component T.
			return {};
		}

		int bit = m_ComponentsToIndex[type];
		if (m_ComponentMap[entity][bit])
		{
			auto& components = *static_cast<std::vector<T>*>(m_SparseMaps[type]);
			return &components[entity];
		}

		return {};
	}

	template <derived_from_component T>
	void Registry::RemoveComponent(entity_id entity)
	{
		auto& type = typeid(T);
		if (!m_ComponentsToIndex.contains(type))
		{
			// TODO: Log warning entity has no component T.
			return;
		}

		// TODO: Remove from dense set.
		m_ComponentMap[entity].set(m_ComponentsToIndex[type], false);
	}

	template <derived_from_component T>
	std::vector<entity_id>* Registry::GetDenseMap()
	{
		auto& type = typeid(T);
		if (m_DenseMaps.contains(type))
		{
			return &m_DenseMaps[type];
		}

		// TODO: Log warning component not registered.
		return nullptr;
	}

	template <derived_from_component T>
	std::vector<T>* Registry::GetSparseMap()
	{
		auto& type = typeid(T);
		if (m_DenseMaps.contains(type))
		{
			return static_cast<std::vector<T>*>(m_SparseMaps[type]);
		}

		// TODO: Log warning component not registered.
		return nullptr;
	}

	template <derived_from_component TComponent>
	void Registry::StoreComponent(entity_id entity,TComponent&& component)
	{
		auto& type = typeid(TComponent);

		auto& components = *static_cast<std::vector<TComponent>*>(m_SparseMaps[type]);
		components[entity] = std::forward<TComponent>(component);
		m_DenseMaps[type].push_back(entity);

		m_ComponentMap[entity].set(m_ComponentsToIndex[type], true);
	}
}

#endif // TETRISENGINE_REGISTRY_H
