#ifndef TETRISENGINE_ENTITY_H
#define TETRISENGINE_ENTITY_H

#include <cstdint>


// TODO: Expand on this, what if id overflows or many empty spots in between id's because of destruction.
// => https://bitsquid.blogspot.com/2014/08/building-data-oriented-entity-system.html

namespace monthly
{
	using entity_id = uint32_t;

	class Entity
	{
	public:
		static entity_id CreateNewEntity();
	private:

		static entity_id m_CurrentEntityIdx;
	};
}

#endif // TETRISENGINE_ENTITY_H