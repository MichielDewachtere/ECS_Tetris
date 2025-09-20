#ifndef TETRISENGINE_RENDERER_H
#define TETRISENGINE_RENDERER_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Singleton.h"
#include "Deleters.h"

namespace monthly
{
	class Registry;

	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* pWindow, Registry& pRegistry);

		void Render() const;

		int GetRenderWidth() const { return m_RenderWidth; }
		int GetRenderHeight() const { return m_RenderHeight; }

		void RenderRectangle(const glm::ivec4& rect, bool isFilled, glm::u8vec4 color) const;
		void RenderLine(int x1, int y1, int x2, int y2, glm::u8vec4 color) const;

	private:
		friend class Singleton<Renderer>;
		explicit Renderer() = default;

		std::unique_ptr<SDL_Renderer, SDLDeleter> m_pRenderer{};

		int m_RenderHeight, m_RenderWidth;

		Registry* m_pRegistry{ nullptr };
	};
}

#endif // TETRISENGINE_RENDERER_H