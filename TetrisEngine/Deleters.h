#ifndef TETRISENGINE_DELETERS_H
#define TETRISENGINE_DELETERS_H

#include <SDL_video.h>
#include <SDL_render.h>

namespace monthly
{
	struct SDLDeleter
	{
		void operator()(SDL_Window* pWindow) const { SDL_DestroyWindow(pWindow); }
		void operator()(SDL_Renderer* pRenderer) const { SDL_DestroyRenderer(pRenderer); }
	};
}

#endif // TETRISENGINE_DELETERS_H