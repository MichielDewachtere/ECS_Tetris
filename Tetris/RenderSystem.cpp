#include "RenderSystem.h"

#include <Entity.h>
#include <Registry.h>

#include "Components.h"
#include "Renderer.h"

RenderSystem::RenderSystem(monthly::Registry& pRegistry)
	: GraphicsSystem(pRegistry)
{
	monthly::entity_id gridIdx = m_pRegistry->GetDenseMap<GridComponent>()->front();
	m_pGridComponent = m_pRegistry->GetComponent<GridComponent>(gridIdx).value();
	m_pGridPositionComponent = m_pRegistry->GetComponent<PositionComponent>(gridIdx).value();
}

void RenderSystem::Render()
{
	auto& renderer = monthly::Renderer::GetInstance();
#ifndef NDEGUB
	RenderDebugGrid(renderer);
#endif // NDEBUG

	RenderPlayField(renderer);
	RenderTetrominos(renderer);
}

void RenderSystem::RenderDebugGrid(const monthly::Renderer& renderer)
{
	const int renderWidth = renderer.GetRenderWidth();
	const int renderHeight = renderer.GetRenderHeight();

	const int cols = renderWidth / cell_size;
	for (int i = 1; i <= cols; ++i)
	{
		renderer.RenderLine(i * cell_size, 0, i * cell_size, renderHeight, { 128,128,128,255 });
	}

	const int rows = renderHeight / cell_size;
	for (int i = 1; i <= rows; ++i)
	{
		renderer.RenderLine(0, i * cell_size, renderWidth, i * cell_size, { 128,128,128,255 });
	}
}
void RenderSystem::RenderPlayField(const monthly::Renderer& renderer)
{
	int x = m_pGridPositionComponent->GetGlobalX() * cell_size;
	int y = m_pGridPositionComponent->GetGlobalY() * cell_size;

	renderer.RenderRectangle(
		{
			x,
			y,
			m_pGridComponent->grid.front().size() * cell_size,
			m_pGridComponent->grid.size() * cell_size },
			false,
		{ 255,255,255,255 }
		);

	auto grid = m_pGridComponent->grid;
	for (size_t i = 0; i < m_pGridComponent->grid.size(); ++i)
	{
		for (size_t j = 0; j < m_pGridComponent->grid.front().size(); ++j)
		{
			if (grid[i][j])
			{
				renderer.RenderRectangle(
					{
						x + j * cell_size,
						y + i * cell_size,
						cell_size,
						cell_size },
						true,
					{ 0,255,255,255 }
					);
			}
		}
	}
}
void RenderSystem::RenderTetrominos(const monthly::Renderer& renderer)
{
	auto idcs = *m_pRegistry->GetDenseMap<TetrominoComponent>();
	for (auto idx : idcs)
	{
		TetrominoComponent* tetromino = m_pRegistry->GetComponent<TetrominoComponent>(idx).value();
		PositionComponent* pos = m_pRegistry->GetComponent<PositionComponent>(idx).value();

		for (size_t i = 0; i < tetromino->shape.size(); ++i)
		{
			for (size_t j = 0; j < tetromino->shape[i].size(); ++j)
			{
				if (tetromino->shape[i][j] == 1)
				{
					renderer.RenderRectangle(
						{
							(pos->GetGlobalX() + j) * cell_size,
							(pos->GetGlobalY() + i) * cell_size,
							cell_size,
							cell_size },
							true,
						{ 255,0,255,255 }
						);
				}
			}
		}

#ifndef NDEBUG
		renderer.RenderRectangle(
			{
				pos->GetGlobalX() * cell_size,
				pos->GetGlobalY() * cell_size,
				cell_size * tetromino->shape.front().size(),
				cell_size * tetromino->shape.size() },
				false,
			{ 255,255,255,255 }
			); 
#endif // NDEBUG
	}
}
