#ifndef TETRISENGINE_BASESYSTEM_H
#define TETRISENGINE_BASESYSTEM_H

#include <cstdint>

//#include "EngineConcepts.h"

namespace monthly
{
	//template <derived_from_component ...>
	class BaseSystem
	{
	public:
		explicit BaseSystem(uint8_t orderIdx = 1);
		virtual ~BaseSystem() = default;

		virtual void Update() = 0;

		uint8_t GetOrderIndex() const { return m_OrderIdx; }

	private:
		uint8_t m_OrderIdx = 1;
	};
}

#endif // TETRISENGINE_BASESYSTEM_H