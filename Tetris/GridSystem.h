#ifndef TETRIS_GRIDSYSTEM_H
#define TETRIS_GRIDSYSTEM_H

#include <vector>
#include <array>
#include <glm/vec2.hpp>

#include "BaseSystem.h"
//#include "Components.h"
#include "Entity.h"
#include "Observer.h"

struct GridComponent;
struct TetrominoComponent;

class GridSystem final
	: public monthly::BaseSystem
	, public monthly::Observer<const glm::ivec2&, TetrominoComponent*>
{
public:
	GridSystem(monthly::Registry& registry, monthly::entity_id grid);
	virtual ~GridSystem() override = default;

	void Update() override {}

	void HandleEvent(const glm::ivec2&, TetrominoComponent*) override;
	void OnSubjectDestroy() override;

private:
	GridComponent* m_pGridComponent{ nullptr };

	std::pair<std::array<int, 4>, int> FillInGrid(const glm::ivec2& pos, TetrominoComponent* tetromino) const;
	void RemoveRows(const std::array<int, 4>& rowsToRemove) const;

	static constexpr int invalid_row{ -1 };
};

#endif // TETRIS_GRIDSYSTEM_H