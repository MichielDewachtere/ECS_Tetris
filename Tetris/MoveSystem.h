#ifndef TETRIS_MOVESYSTEM_H
#define TETRIS_MOVESYSTEM_H

#include <glm/vec2.hpp>

#include <BaseSystem.h>
#include <Subject.h>

#include "Components.h"

class MoveSystem final : public monthly::BaseSystem
{
public:
	MoveSystem(monthly::Registry& registry);
	virtual ~MoveSystem() override = default;

	void Update() override;

	monthly::Subject<const glm::ivec2, TetrominoComponent*> tetrominoLockedIn;

private:
	GridComponent* m_pGridComponent{ nullptr };
	TetrominoComponent* m_pActiveTetromino{ nullptr };
	PositionComponent* m_pActivePositionComponent{ nullptr };

	float m_AccuTime{ 0.f };
	float m_MoveDownTime{ 1.f };

	void Move();
	void MoveHorizontal(bool left) const;
	void MoveDown(bool drop) const;
	bool MoveDownHelper(int& yPosOffset) const;

	bool GetNewActiveTetromino();

	void ShapeLockedIn(int yOffset) const;
};

#endif // TETRIS_MOVESYSTEM_H