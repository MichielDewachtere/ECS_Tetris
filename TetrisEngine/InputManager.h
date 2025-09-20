#ifndef TETRISENGINE_INPUTMANAGER_H
#define TETRISENGINE_INPUTMANAGER_H

#include <array>

#include <SDL.h>

#include "Singleton.h"

namespace monthly
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		virtual ~InputManager() override = default;

		InputManager(const InputManager& other) = delete;
		InputManager& operator=(const InputManager& rhs) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(InputManager&& rhs) = delete;

		bool Update();

		bool IsKeyPressed(SDL_Scancode key) const;
		bool IsKeyReleased(SDL_Scancode key) const;
		bool IsKeyDown(SDL_Scancode key) const;

	private:
		friend class Singleton<InputManager>;
		InputManager();

		std::array<uint8_t, SDL_NUM_SCANCODES> m_CurKeyState{};
		std::array<uint8_t, SDL_NUM_SCANCODES> m_PrevKeyState{};
	};
}

#endif // TETRISENGINE_INPUTMANAGER_H