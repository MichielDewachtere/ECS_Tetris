#include "TetrisEngine.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <stdexcept>

namespace
{
	void PrintSDLVersion()
	{
		SDL_version version;
		SDL_VERSION(&version)
			printf("We compiled against SDL version %u.%u.%u ...\n",
				version.major, version.minor, version.patch);

		SDL_GetVersion(&version);
		printf("We are linking against SDL version %u.%u.%u.\n",
			version.major, version.minor, version.patch);

		SDL_IMAGE_VERSION(&version)
			printf("We compiled against SDL_image version %u.%u.%u ...\n",
				version.major, version.minor, version.patch);

		version = *IMG_Linked_Version();
		printf("We are linking against SDL_image version %u.%u.%u.\n",
			version.major, version.minor, version.patch);

		SDL_TTF_VERSION(&version)
			printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
				version.major, version.minor, version.patch);

		version = *TTF_Linked_Version();
		printf("We are linking against SDL_ttf version %u.%u.%u.\n",
			version.major, version.minor, version.patch);
	}
}

monthly::TetrisEngine::TetrisEngine(WindowSettings settings)
{
	m_WindowSettings = std::move(settings);
	m_WindowSettings.frameTime = 1.f / static_cast<float>(m_WindowSettings.fps);

	PrintSDLVersion();

	InitWindow(m_WindowSettings.windowTitle, m_WindowSettings.width, m_WindowSettings.height);
}

void monthly::TetrisEngine::InitWindow(const std::string& name, int width, int height, uint32_t flags)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = std::unique_ptr<SDL_Window, SDLDeleter>(
		SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags),
		SDLDeleter()
	);

	if (m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
}
