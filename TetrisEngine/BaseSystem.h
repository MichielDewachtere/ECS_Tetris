#ifndef TETRISENGINE_BASESYSTEM_H
#define TETRISENGINE_BASESYSTEM_H

#include <cstdint>

//#include "EngineConcepts.h"

namespace monthly
{
	class Registry;

	//template <derived_from_component ...>
	class BaseSystem
	{
	public:
		explicit BaseSystem(Registry& registry, uint8_t orderIdx = 1);
		virtual ~BaseSystem() = default;

		virtual void Update() {}

		uint8_t GetOrderIndex() const { return m_OrderIdx; }

	protected:
		Registry* m_pRegistry;

	private:
		uint8_t m_OrderIdx = 1;
	};
}

#endif // TETRISENGINE_BASESYSTEM_H