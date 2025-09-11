#ifndef TETRISENGINE_ENGINECONCEPTS_H
#define TETRISENGINE_ENGINECONCEPTS_H

#include <type_traits>

#include "BaseComponent.h"
#include "BaseSystem.h"
#include "GraphicsSystem.h"

namespace monthly
{
	template <typename T>
	concept derived_from_component = std::is_base_of_v<BaseComponent, T>;

	template <typename T>
	concept derived_from_system = std::is_base_of_v<BaseSystem, T>;

	template <typename T>
	concept derived_from_graphics_system = std::is_base_of_v<GraphicsSystem, T>;

    template<typename T>
    concept unsigned_integer =
        std::is_same_v<T, uint8_t> ||
        std::is_same_v<T, uint16_t> ||
        std::is_same_v<T, uint32_t> ||
        std::is_same_v<T, uint64_t> ||
        std::is_same_v<T, unsigned char> ||
        std::is_same_v<T, unsigned short> ||
        std::is_same_v<T, unsigned int> ||
        std::is_same_v<T, unsigned long> ||
        std::is_same_v<T, unsigned long long>;
}


#endif // TETRISENGINE_ENGINECONCEPTS_H