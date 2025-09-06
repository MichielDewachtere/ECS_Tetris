#ifndef TETRISENGINE_TETRISENGINE_H
#define TETRISENGINE_TETRISENGINE_H

#include <memory>
#include <string>

#include "Deleters.h"
#include "Registry.h"

namespace monthly
{
	struct WindowSettings
	{
		uint32_t width = 640, height = 480, fps = 60;
		float frameTime = 0.016f;
		std::string windowTitle, dataPath;
	};

	class TetrisEngine final
	{
	public:
		explicit TetrisEngine(WindowSettings settings, const Registry& registry);
		~TetrisEngine() = default;

		TetrisEngine(const TetrisEngine& other) = delete;
		TetrisEngine& operator=(const TetrisEngine& rhs) = delete;
		TetrisEngine(TetrisEngine&& other) = delete;
		TetrisEngine& operator=(TetrisEngine&& rhs) = delete;

		void Run();

		static SDL_Window* GetWindow() { return m_pWindow.get(); }

	private:
		static inline std::unique_ptr<SDL_Window, SDLDeleter> m_pWindow{ nullptr };
		static inline WindowSettings m_WindowSettings{};

		std::unique_ptr<Registry> m_pRegistry;

		static void InitWindow(const std::string& name, int width, int height, uint32_t flags = 0);
	};
}

#endif // TETRISENGINE_TETRISENGINE_H