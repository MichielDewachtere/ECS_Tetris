#include "GridSystem.h"

#include <SDL_rwops.h>

#include "MoveSystem.h"
#include "Registry.h"

GridSystem::GridSystem(monthly::Registry& registry, monthly::entity_id grid)
	: BaseSystem(registry)
{
	auto moveSystem = m_pRegistry->GetSystem<MoveSystem>();
	if (moveSystem.has_value())
	{
		moveSystem.value()->tetrominoLockedIn.AddObserver(this);
	}

	auto gridComponent = m_pRegistry->GetComponent<GridComponent>(grid);
	if (gridComponent.has_value())
		m_pGridComponent = gridComponent.value();
}

void GridSystem::HandleEvent(const glm::ivec2& pos, TetrominoComponent* tetromino)
{
	auto [rowsToRemove, amountOfRowsToRemove] = FillInGrid(pos, tetromino);

	if (amountOfRowsToRemove == 0)
	{
		return;
	}

	// TODO: Notify HUD.
	RemoveRows(rowsToRemove);
}

void GridSystem::OnSubjectDestroy()
{
	auto moveSystem = m_pRegistry->GetSystem<MoveSystem>();
	if (moveSystem.has_value())
	{
		moveSystem.value()->tetrominoLockedIn.RemoveObserver(this);
	}
}

std::pair<std::array<int, 4>, int> GridSystem::FillInGrid(const glm::ivec2& pos, TetrominoComponent* tetromino) const
{
	std::array<int, 4> rowsToRemove{ invalid_row, invalid_row, invalid_row, invalid_row };
	int amountOfRowsToRemove = 0;

	for (size_t i = 0; i < tetromino->shape.size(); ++i)
	{
		for (size_t j = 0; j < tetromino->shape[i].size(); ++j)
		{
			if (!tetromino->shape[i][j])
				continue;

			const size_t gridPosY = pos.y + i;
			const size_t gridPosX = pos.x + j;
			auto& grid = m_pGridComponent->grid;
			grid[gridPosY][gridPosX] = tetromino->color;

			if (std::ranges::find(grid[gridPosY], true, [](const glm::u8vec4& color) -> bool {return color.a == 0;}) == grid[gridPosY].end())
			{
				rowsToRemove[i] = static_cast<int>(gridPosY);
				++amountOfRowsToRemove;
			}
		}
	}

	return { rowsToRemove, amountOfRowsToRemove };
}

void GridSystem::RemoveRows(const std::array<int, 4>& rowsToRemove) const
{
	for (int row : rowsToRemove)
	{
		if (row == invalid_row)
		{
			continue;
		}

		for (int y = row; y > 0; --y)
		{
			m_pGridComponent->grid[y] = m_pGridComponent->grid[y - 1];
		}

		m_pGridComponent->grid[0] = std::vector(m_pGridComponent->grid.front().size(), glm::u8vec4{});
	}
}