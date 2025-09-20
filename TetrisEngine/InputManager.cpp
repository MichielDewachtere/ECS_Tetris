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

	SDL_memcpy(m_PrevKeyState.data(), m_CurKeyState.data(), sizeof(m_CurKeyState));

	const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
	SDL_memcpy(m_CurKeyState.data(), keyboardState, sizeof(m_CurKeyState));

	return true;
}

bool monthly::InputManager::IsKeyPressed(SDL_Scancode key) const
{
	return m_CurKeyState[key] && !m_PrevKeyState[key];
}

bool monthly::InputManager::IsKeyReleased(SDL_Scancode key) const
{
	return !m_CurKeyState[key] && m_PrevKeyState[key];
}

bool monthly::InputManager::IsKeyDown(SDL_Scancode key) const
{
	return m_CurKeyState[key];
}

monthly::InputManager::InputManager() = default;
