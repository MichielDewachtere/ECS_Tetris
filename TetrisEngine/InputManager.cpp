#include "InputManager.h"

#include <SDL_events.h>
#include <SDL_ttf.h>

bool monthly::InputManager::Update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return false;
		}
	}

	return true;
}

monthly::InputManager::InputManager() = default;