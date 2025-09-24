#include "MoveSystem.h"

#include <Entity.h>
#include <Registry.h>

#include "GameTime.h"
#include "InputManager.h"

MoveSystem::MoveSystem(monthly::Registry& registry)
	: BaseSystem(registry)
{
	monthly::entity_id gridIdx = m_pRegistry->GetDenseMap<GridComponent>()->front();
	m_pGridComponent = m_pRegistry->GetComponent<GridComponent>(gridIdx).value();

	GetNewActiveTetromino();
}

void MoveSystem::Update()
{
	if (m_pActiveTetromino->isControlled == false)
	{
		if (GetNewActiveTetromino() == false)
		{
			return;
		}
	}

	Move();
}

void MoveSystem::Move()
{
	const auto& input = monthly::InputManager::GetInstance();

	if (input.IsKeyReleased(SDL_SCANCODE_SPACE))
	{
		MoveDown(true);
		return;
	}

	if (input.IsKeyReleased(SDL_SCANCODE_LEFT))
	{
		MoveHorizontal(true);
	}
	if (input.IsKeyReleased(SDL_SCANCODE_RIGHT))
	{
		MoveHorizontal(false);
	}

	bool isAtBottom = false;
	if (input.IsKeyReleased(SDL_SCANCODE_DOWN))
	{
		MoveDown(false);
	}

	m_AccuTime += monthly::GameTime::GetInstance().GetElapsed();
	if (isAtBottom == false && m_AccuTime > m_MoveDownTime)
	{
		m_AccuTime = 0;
		MoveDown(false);
	}
}

void MoveSystem::MoveHorizontal(bool left) const
{
	const auto shape = m_pActiveTetromino->shape;

	const int shapeWidth = static_cast<int>(shape.front().size());
	const int gridWidth = static_cast<int>(m_pGridComponent->grid.front().size());

	const int dir = left ? -1 : 1;
	const int xPos = m_pActivePositionComponent->GetLocalX() + (left ? 0 : shapeWidth - 1);
	const int futurePos = xPos + dir;

	for (size_t row = 0; row < shape.size(); ++row)
	{
		const int startCol = left ? 0 : shapeWidth - 1;
		const int endCol = left ? shapeWidth : -1;
		const int step = left ? 1 : -1;

		for (int col = startCol; col != endCol; col += step) 
		{
			if (shape[row][col] == 0)
				continue;

			int posToCheck;
			if (left)
			{
				if (futurePos + col < 0)
					return;

				posToCheck = futurePos + col;
			}
			else
			{
				if (futurePos - (startCol - col) >= gridWidth)
					return;

				posToCheck = futurePos - (startCol - col);
			}

			if (m_pGridComponent->grid[m_pActivePositionComponent->GetLocalY() + row][posToCheck].a)
				return;
		}
	}

	m_pActivePositionComponent->SetGlobalX(m_pActivePositionComponent->GetGlobalX() + dir);
}
void MoveSystem::MoveDown(bool drop) const
{
	int yOffset = 0;
	if (drop)
	{
		while (MoveDownHelper(yOffset)) {}
		ShapeLockedIn(yOffset);
	}
	else
	{
		if (!MoveDownHelper(yOffset))
		{
			ShapeLockedIn(yOffset);
		}
	}

	m_pActivePositionComponent->SetGlobalY(m_pActivePositionComponent->GetGlobalY() + yOffset);
}

bool MoveSystem::MoveDownHelper(int& yOffset) const
{
	const auto shape = m_pActiveTetromino->shape;

	const int shapeWidth = static_cast<int>(shape.front().size());
	const int shapeHeight = static_cast<int>(shape.size());

	const int gridHeight = static_cast<int>(m_pGridComponent->grid.size());

	for (int row = shapeHeight - 1; row >= 0; --row)
	{
		for (int col = 0; col < shapeWidth; ++col)
		{
			if (shape[row][col] == 0)
				continue;

			int yPos = m_pActivePositionComponent->GetLocalY() + row + yOffset;
			if (yPos == gridHeight - 1)
			{
				return false;
			}

			if (m_pGridComponent->grid[yPos + 1][m_pActivePositionComponent->GetLocalX() + col].a)
			{
				return false;
			}
		}
	}

	++yOffset;
	return true;
}

bool MoveSystem::GetNewActiveTetromino()
{
	std::vector<monthly::entity_id> tetrominos = *m_pRegistry->GetDenseMap<TetrominoComponent>();

	for (auto idx : tetrominos)
	{
		TetrominoComponent* tetromino = m_pRegistry->GetComponent<TetrominoComponent>(idx).value();
		if (tetromino->isControlled == false)
			continue;

		m_pActiveTetromino = tetromino;

		auto posResult = m_pRegistry->GetComponent<PositionComponent>(idx);
		if (!posResult.has_value())
			continue;

		m_pActivePositionComponent = posResult.value();

		return true;
	}

	return false;
}

void MoveSystem::ShapeLockedIn(int yOffset) const
{
	const int x = m_pActivePositionComponent->GetLocalX();
	const int y = m_pActivePositionComponent->GetLocalY() + yOffset;
	tetrominoLockedIn.Notify(glm::ivec2{ x,y }, m_pActiveTetromino);

	//m_pActivePositionComponent = nullptr;
	//m_pActiveTetromino = nullptr;
}
