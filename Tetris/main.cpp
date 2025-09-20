#include <iostream>

#include <TetrisEngine.h>
#include <Registry.h>

#include "Components.h"

#include "MoveSystem.h"
#include "RenderSystem.h"
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
        PositionComponent(5, 3),
        GridComponent{ .grid = std::vector(20, std::vector(10, false)) }
        //GridComponent{ .grid = std::vector(20, std::vector<bool>{0,0,1,0,0,0,0,0,0,1}) }
    );

	// 'L'
    registry->RegisterEntity(
        EntityComponent{.parent = grid },
        PositionComponent{ 9,3 },
        TetrominoComponent{ .isControlled = true,
            .shape = {
            { 0, 1, 0 },
            { 0, 1, 0 },
            { 0, 1, 1 }}
        }
    );

    // '-'
    //registry->RegisterEntity(
    //    PositionComponent{ .globalX = 4, .globalY = -1 },
    //    TetrominoComponent{ .isControlled = true,
    //        .shape = {
    //        { 0, 1, 0, 0, 0 },
    //        { 0, 1, 0, 0, 0 },
    //        { 0, 1, 0, 0, 0 },
    //        { 0, 1, 0, 0, 0 }}
    //    }
    //);

    registry->RegisterSystem<TransformSystem>(new TransformSystem(*registry));
    registry->RegisterSystem<MoveSystem>(new MoveSystem(*registry));
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
