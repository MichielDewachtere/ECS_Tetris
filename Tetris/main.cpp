#include <iostream>

#include "BaseSystem.h"
#include "Renderer.h"
#include "TetrisEngine.h"

struct PositionComponent : monthly::BaseComponent
{
    float x, y;
};

struct ColorComponent : monthly::BaseComponent
{
    uint8_t r, g, b, a;
};

struct VelocityComponent : monthly::BaseComponent
{
    float x, y;
};

class DebugSystem : public monthly::GraphicsSystem
{
public:
	DebugSystem(monthly::Registry& registry)
		: GraphicsSystem(registry) {}

    void Render() override
    {
        auto& pRenderer = monthly::Renderer::GetInstance();

		std::vector<monthly::entity_id> colorComponents = *m_pRegistry->GetDenseMap<ColorComponent>();

		for (auto idx : colorComponents)
        {
            auto result = m_pRegistry->GetComponent<PositionComponent>(idx);
            if (!result.has_value())
                continue;

            auto posComp = result.value();
        	auto colorComp = m_pRegistry->GetComponent<ColorComponent>(idx).value();
            pRenderer.RenderRectangle({ posComp->x, posComp->y, 20,20 }, true, 
                { colorComp->r, colorComp->g, colorComp->b,colorComp->a });
        }
    }
};

class MoveSystem : public monthly::BaseSystem
{
public:
    MoveSystem(monthly::Registry& registry)
		: BaseSystem(registry) {}

	virtual void Update() override
    {
        std::vector<monthly::entity_id> velocityComponents = *m_pRegistry->GetDenseMap<VelocityComponent>();

        for (auto idx : velocityComponents)
        {
            auto result = m_pRegistry->GetComponent<PositionComponent>(idx);
            if (!result.has_value())
                continue;

            auto posComp = result.value();
            auto velComp	= m_pRegistry->GetComponent<VelocityComponent>(idx).value();

            posComp->x += velComp->x;
            posComp->y += velComp->y;
        }
    }
};

int main()
{
    monthly::WindowSettings settings{
        .width = 512,
        .height = 480,
        .fps = 60,
        .windowTitle = "ECS Tetris demo",
    };

	auto registry = new monthly::Registry();
    registry->RegisterComponent<PositionComponent>();
    registry->RegisterComponent<VelocityComponent>();
    registry->RegisterComponent<ColorComponent>();

    registry->RegisterEntity(
        PositionComponent{ .x = 100,.y = 100 }, 
        ColorComponent{ .r = 255,.g = 0,.b = 0,.a = 255 }
    );

    registry->RegisterEntity(
        PositionComponent{ .x = 100, .y = 200 },
        ColorComponent{ .r = 0,.g = 255,.b = 0,.a = 255 }
    );

    registry->RegisterEntity(
        PositionComponent{ .x = 100, .y = 300 },
        VelocityComponent{ .x = 0.001f, .y = 0.002f },
        ColorComponent{ .r = 0,.g = 0,.b = 255,.a = 255 }
    );

    registry->RegisterSystem<DebugSystem>(new DebugSystem(*registry));
    registry->RegisterSystem<MoveSystem>(new MoveSystem(*registry));

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