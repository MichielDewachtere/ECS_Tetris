#ifndef TETRIS_TETROMINOSYSTEM_H
#define TETRIS_TETROMINOSYSTEM_H

#include <unordered_map>
#include <glm/vec2.hpp>
#include <glm/ext/vector_uint4_sized.hpp>

#include "BaseSystem.h"
#include "Observer.h"

struct TetrominoComponent;
struct PositionComponent;

class TetrominoSystem final
	: public monthly::BaseSystem
	, public monthly::Observer<const glm::ivec2&, TetrominoComponent*>
{
public:
	TetrominoSystem(monthly::Registry& registry);
	virtual ~TetrominoSystem() override = default;

	virtual void Update() override;

	void HandleEvent(const glm::ivec2&, TetrominoComponent*) override;
	void OnSubjectDestroy() override {}

private:
	enum Tetromino : uint8_t
	{
		I = 0,
		O = 1,
		T = 2,
		S = 3,
		Z = 4,
		J = 5,
		L = 6,
		amount = 7
	};

	bool m_IsDirty{ false };
	glm::ivec2 m_GridOrigin{};

	TetrominoComponent* m_pActiveTetrominoComponent{ nullptr };
	PositionComponent* m_pActivePositionComponent{ nullptr };

	Tetromino m_DisplayTetromino{};
	TetrominoComponent* m_pDisplayTetrominoComponent{ nullptr };

	static Tetromino GetRandomTetromino();

	static const inline std::unordered_map<Tetromino, std::vector<std::vector<bool>>> tetromino_to_shape{
		{ Tetromino::I,
			{
				{0,0,0,0},
				{0,0,0,0},
				{1,1,1,1},
				{0,0,0,0},
			}
		},
		{ Tetromino::O,
			{
				{1,1},
				{1,1}
			}
		},
		{ Tetromino::T,
			{
				{0,0,0},
				{1,1,1},
				{0,1,0},
			}
		},
		{ Tetromino::S,
			{
				{0,0,0},
				{0,1,1},
				{1,1,0},
			}
		},
		{ Tetromino::Z,
			{
				{0,0,0},
				{1,1,0},
				{0,1,1},
			}
		},
		{ Tetromino::J,
			{
				{0,0,0},
				{1,1,1},
				{0,0,1},
			}
		},
		{ Tetromino::L,
			{
				{0,0,0},
				{1,1,1},
				{1,0,0},
			}
		}
	};
	static const inline std::unordered_map<Tetromino, glm::ivec2> tetromino_to_pos{
		{ Tetromino::I, {3,-2} },
		{ Tetromino::O, {5, 0} },
		{ Tetromino::T, {4,-1} },
		{ Tetromino::S, {4,-1} },
		{ Tetromino::Z, {4,-1} },
		{ Tetromino::J, {4,-1} },
		{ Tetromino::L, {4,-1} }
	};
	static const inline std::unordered_map<Tetromino, glm::u8vec4> tetromino_to_color{
	{ Tetromino::I, {0,		255,	255,	255} },
	{ Tetromino::O, {255,	255,	0,	255} },
	{ Tetromino::T, {255,	0,	255,	255} },
	{ Tetromino::S, {0,		255,	0,	255} },
	{ Tetromino::Z, {255,	0,	0,	255} },
	{ Tetromino::J, {0	,	0,	255,	255} },
	{ Tetromino::L, {255,	165,	0,	255} }
	};
};

#endif // TETRIS_TETROMINOSYSTEM_H