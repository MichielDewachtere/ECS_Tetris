#ifndef TETRISENGINE_ENTITY_H
#define TETRISENGINE_ENTITY_H

#include <cstdint>

using entity_id = uint32_t;

// TODO: Expand on this, what if id overflows or many empty spots in between id's because of destruction.
// => https://bitsquid.blogspot.com/2014/08/building-data-oriented-entity-system.html

namespace monthly
{
	static inline entity_id g_currentEntityIdx = 0;

	entity_id CreateNewEntity()
	{
		return g_currentEntityIdx++;
	}
}

#endif // TETRISENGINE_ENTITY_H