#ifndef TETRISENGINE_GRAPHICSSYSTEM_H
#define TETRISENGINE_GRAPHICSSYSTEM_H

#include "BaseSystem.h"

namespace monthly
{
	class GraphicsSystem : public BaseSystem
	{
	public:
		explicit GraphicsSystem(Registry& pRegistry, uint8_t orderIdx = 1) : BaseSystem(pRegistry, orderIdx) {}
		virtual ~GraphicsSystem() override = default;

		virtual void Render() {}
	};
}

#endif // TETRISENGINE_GRAPHICSSYSTEM_H