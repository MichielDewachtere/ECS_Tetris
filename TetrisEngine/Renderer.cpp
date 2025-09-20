#include "Renderer.h"

#include <stdexcept>
#include <string>

#include "Registry.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void monthly::Renderer::Init(SDL_Window* pWindow, Registry& pRegistry)
{
	m_pRenderer = std::unique_ptr<SDL_Renderer, SDLDeleter>(SDL_CreateRenderer(pWindow, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED));
	if (m_pRenderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	m_pRegistry = &pRegistry;
	SDL_GetRendererOutputSize(m_pRenderer.get(), &m_RenderWidth, &m_RenderHeight);
}

void monthly::Renderer::Render() const
{
	SDL_SetRenderDrawColor(m_pRenderer.get(), 0, 0, 0, 1);
	SDL_RenderClear(m_pRenderer.get());

	m_pRegistry->Render();

	SDL_RenderPresent(m_pRenderer.get());
}

void monthly::Renderer::RenderRectangle(const glm::ivec4& rect, bool isFilled, glm::u8vec4 color) const
{
	SDL_Color originalColor;
	SDL_GetRenderDrawColor(m_pRenderer.get(), &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);

	const SDL_Rect sdlRect{ rect.x, rect.y, rect.z, rect.w };

	SDL_SetRenderDrawColor(m_pRenderer.get(), color.r, color.g, color.b, color.a);
	if (isFilled)
		SDL_RenderFillRect(m_pRenderer.get(), &sdlRect);
	else
		SDL_RenderDrawRect(m_pRenderer.get(), &sdlRect);

	SDL_SetRenderDrawColor(m_pRenderer.get(), originalColor.r, originalColor.g, originalColor.b, originalColor.a);
	SDL_SetRenderTarget(m_pRenderer.get(), nullptr);
}

void monthly::Renderer::RenderLine(int x1, int y1, int x2, int y2, glm::u8vec4 color) const
{
	SDL_Color originalColor;
	SDL_GetRenderDrawColor(m_pRenderer.get(), &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);

	SDL_SetRenderDrawColor(m_pRenderer.get(), color.r, color.g, color.b, color.a);

	SDL_RenderDrawLine(m_pRenderer.get(), x1, y1, x2, y2);

	SDL_SetRenderDrawColor(m_pRenderer.get(), originalColor.r, originalColor.g, originalColor.b, originalColor.a);
	SDL_SetRenderTarget(m_pRenderer.get(), nullptr);
}
