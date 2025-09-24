#include "TetrominoSystem.h"

#include <random>

#include "Registry.h"

#include "Components.h"
#include "MoveSystem.h"

TetrominoSystem::TetrominoSystem(monthly::Registry& registry)
	: BaseSystem(registry)
{
	const auto idcs = *m_pRegistry->GetDenseMap<TetrominoComponent>();
	for	(const monthly::entity_id id : idcs)
	{
		TetrominoComponent* comp = m_pRegistry->GetComponent<TetrominoComponent>(id).value();
		if (comp->isControlled)
		{
			m_pActiveTetrominoComponent = comp;
			m_pActivePositionComponent = m_pRegistry->GetComponent<PositionComponent>(id).value();
			m_GridOrigin = glm::ivec2{ m_pActivePositionComponent->GetGlobalX(), m_pActivePositionComponent->GetGlobalY() };

			Tetromino tetromino = GetRandomTetromino();
			m_pActiveTetrominoComponent->shape = tetromino_to_shape.at(tetromino);
			m_pActiveTetrominoComponent->color = tetromino_to_color.at(tetromino);
			m_pActivePositionComponent->IncrementGlobalX(tetromino_to_pos.at(tetromino).x);
			m_pActivePositionComponent->IncrementGlobalY(tetromino_to_pos.at(tetromino).y);
		}
		else
		{
			m_pDisplayTetrominoComponent = comp;

			m_DisplayTetromino = GetRandomTetromino();
			m_pDisplayTetrominoComponent->shape = tetromino_to_shape.at(m_DisplayTetromino);
			m_pDisplayTetrominoComponent->color = tetromino_to_color.at(m_DisplayTetromino);
		}
	}

	const auto moveSystem = m_pRegistry->GetSystem<MoveSystem>();
	if (moveSystem.has_value())
	{
		moveSystem.value()->tetrominoLockedIn.AddObserver(this);
	}
}

void TetrominoSystem::Update()
{
	if (!m_IsDirty)
	{
		return;
	}

	// TODO: Check if can spawn, if not => game over

	glm::ivec2 tetrominoSpawnPos = m_GridOrigin + tetromino_to_pos.at(m_DisplayTetromino);
	m_pActivePositionComponent->SetGlobalX(tetrominoSpawnPos.x);
	m_pActivePositionComponent->SetGlobalY(tetrominoSpawnPos.y);

	m_pActiveTetrominoComponent->shape = tetromino_to_shape.at(m_DisplayTetromino);
	m_pActiveTetrominoComponent->color = tetromino_to_color.at(m_DisplayTetromino);

	m_DisplayTetromino = GetRandomTetromino();
	m_pDisplayTetrominoComponent->shape = tetromino_to_shape.at(m_DisplayTetromino);
	m_pDisplayTetrominoComponent->color = tetromino_to_color.at(m_DisplayTetromino);

	m_IsDirty = false;
}

void TetrominoSystem::HandleEvent(const glm::ivec2&, TetrominoComponent*)
{
	m_IsDirty = true;
}

TetrominoSystem::Tetromino TetrominoSystem::GetRandomTetromino()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int> dis(0, static_cast<int>(Tetromino::amount) - 1);

	return static_cast<Tetromino>(dis(gen));
}

