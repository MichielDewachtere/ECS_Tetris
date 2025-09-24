#ifndef TETRIS_ROTATESYSTEM_H
#define TETRIS_ROTATESYSTEM_H

#include "BaseSystem.h"
#include "Entity.h"

struct TetrominoComponent;
struct PositionComponent;
struct GridComponent;

class RotateSystem final : public monthly::BaseSystem
{
public:
	RotateSystem(monthly::Registry& registry, monthly::entity_id activeTetromino, monthly::entity_id grid);
	virtual void Update() override;

private:
	GridComponent* m_pGridComponent{ nullptr };
	TetrominoComponent* m_pTetrominoComponent{ nullptr };
	PositionComponent* m_pTetrominoPosComponent{ nullptr };

	void RotateShape() const;
};

#endif // TETRIS_ROTATESYSTEM_H