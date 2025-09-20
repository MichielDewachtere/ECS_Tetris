#ifndef TETRIS_RENDERSYSTEM_H
#define TETRIS_RENDERSYSTEM_H

#include <GraphicsSystem.h>

struct PositionComponent;

namespace monthly
{
	class Renderer;
}

struct GridComponent;

class RenderSystem final : public monthly::GraphicsSystem
{
public:
	RenderSystem(monthly::Registry& pRegistry);

	void Render() override;

private:
	GridComponent* m_pGridComponent{ nullptr };
	PositionComponent* m_pGridPositionComponent{ nullptr };

	static void RenderDebugGrid(const monthly::Renderer& renderer);
	void RenderPlayField(const monthly::Renderer& renderer);
	void RenderTetrominos(const monthly::Renderer& renderer);

	constexpr static int cell_size = 24;
};

#endif // TETRIS_RENDERSYSTEM_H
