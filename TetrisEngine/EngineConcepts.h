#ifndef TETRISENGINE_ENGINECONCEPTS_H
#define TETRISENGINE_ENGINECONCEPTS_H

#include <type_traits>

#include "BaseComponent.h"
#include "BaseSystem.h"

template <typename T>
concept derived_from_component = std::is_base_of_v<BaseComponent, T>;

template <typename T>
concept derived_from_service = std::is_base_of_v<BaseSystem, T>;


#endif // TETRISENGINE_ENGINECONCEPTS_H