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
	concept derived_from_graphics_service = std::is_base_of_v<GraphicsSystem, T>;
}


#endif // TETRISENGINE_ENGINECONCEPTS_H