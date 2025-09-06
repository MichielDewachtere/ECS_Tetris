#ifndef TETRISENGINE_INPUTMANAGER_H
#define TETRISENGINE_INPUTMANAGER_H
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

	private:
		friend class Singleton<InputManager>;
		InputManager();

	};
}

#endif // TETRISENGINE_INPUTMANAGER_H