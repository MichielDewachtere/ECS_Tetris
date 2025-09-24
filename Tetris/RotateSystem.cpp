#include "RotateSystem.h"

#include "Components.h"
#include "InputManager.h"
#include "Registry.h"

RotateSystem::RotateSystem(monthly::Registry& registry, monthly::entity_id activeTetromino, monthly::entity_id grid)
	: BaseSystem(registry)
{
	m_pTetrominoComponent = m_pRegistry->GetComponent<TetrominoComponent>(activeTetromino).value();
	m_pTetrominoPosComponent = m_pRegistry->GetComponent<PositionComponent>(activeTetromino).value();
	m_pGridComponent = m_pRegistry->GetComponent<GridComponent>(grid).value();
}

void RotateSystem::Update()
{
	auto& input = monthly::InputManager::GetInstance();

	if (input.IsKeyPressed(SDL_SCANCODE_UP))
	{
		RotateShape();
	}
}

void RotateSystem::RotateShape() const
{
	size_t size = m_pTetrominoComponent->shape.size();
	std::vector rotatedShape(size, std::vector(size, false));

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			rotatedShape[j][size - 1 - i] = m_pTetrominoComponent->shape[i][j];

			const int gridXPos = static_cast<int>(m_pTetrominoPosComponent->GetLocalX() + j);
			const int gridYPos = static_cast<int>(m_pTetrominoPosComponent->GetLocalY() + size - 1 - i);

			if (gridXPos < 0 || gridXPos >= static_cast<int>(m_pGridComponent->grid.front().size())
				|| gridYPos >= static_cast<int>(m_pGridComponent->grid.size())
				|| m_pGridComponent->grid[gridYPos][gridXPos].a)
			{
				return;
			}
		}
	}

	m_pTetrominoComponent->shape = rotatedShape;
}
