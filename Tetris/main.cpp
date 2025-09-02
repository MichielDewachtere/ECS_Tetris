#include <iostream>

#include "TetrisEngine.h"

int main()
{
    monthly::WindowSettings settings{
        .width = 512,
        .height = 480,
        .fps = 60,
        .windowTitle = "ECS Tetris demo",
    };

#ifndef NDEBUG
    [[maybe_unused]] monthly::TetrisEngine engine(settings);
#else
    try
    {
        [[maybe_unused]] monthly::TetrisEngine engine(settings);
        //engine.Run(load);
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
    }

#endif // NDEBUG

    std::cout << "Hello from Tetris Game!\n";
}