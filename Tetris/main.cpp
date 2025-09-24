#include <iostream>

#include <TetrisEngine.h>
#include <Registry.h>

#include "Components.h"
#include "GridSystem.h"

#include "MoveSystem.h"
#include "RenderSystem.h"
#include "RotateSystem.h"
#include "TetrominoSystem.h"
#include "TransformSystem.h"

int main()
{
    monthly::WindowSettings settings{
        .width = 528 * 2,
        .height = 480 * 2,
        .fps = 60,
        .windowTitle = "ECS Tetris demo",
    };

	auto registry = new monthly::Registry();
    registry->RegisterComponent<EntityComponent>();
    registry->RegisterComponent<GridComponent>();
    registry->RegisterComponent<PositionComponent>();
    registry->RegisterComponent<TetrominoComponent>();
    registry->RegisterComponent<RotationComponent>();

    monthly::entity_id grid = registry->RegisterEntity(
        EntityComponent(),
        PositionComponent(5, -1),
        GridComponent{ .grid = std::vector(24, std::vector(10, glm::u8vec4{})) }
    );

    monthly::entity_id activeTetromino = registry->RegisterEntity(
        EntityComponent{.parent = grid },
        PositionComponent(5, 3),
        TetrominoComponent{ .isControlled = true,
            .shape = {}
        }
    );

    registry->RegisterEntity(
        EntityComponent{ .parent = grid },
        PositionComponent( 16,10 ),
        TetrominoComponent{ .isControlled = false,
            .shape = {}
        }
    );

	registry->RegisterSystem<TransformSystem>(new TransformSystem(*registry));

	registry->RegisterSystem<MoveSystem>(new MoveSystem(*registry));
	registry->RegisterSystem<RotateSystem>(new RotateSystem(*registry, activeTetromino, grid));
    registry->RegisterSystem<TetrominoSystem>(new TetrominoSystem(*registry));
    registry->RegisterSystem<GridSystem>(new GridSystem(*registry, grid));

    registry->RegisterSystem<RenderSystem>(new RenderSystem(*registry));

#ifndef NDEBUG
    monthly::TetrisEngine engine(settings, *registry);
    engine.Run();
#else
    try
    {
        [[maybe_unused]] monthly::TetrisEngine engine(settings);
		engine.Run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }

#endif // NDEBUG

    std::cout << "Hello from Tetris Game!\n";
}
