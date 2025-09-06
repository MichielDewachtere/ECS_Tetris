#ifndef TETRISENGINE_SINGLETON_H
#define TETRISENGINE_SINGLETON_H

#include <memory>

namespace monthly
{
	template <typename T>
	class Singleton
	{
	public:
		virtual ~Singleton() = default;

		static T& GetInstance()
		{
			if (!m_Instance)
			{
				m_Instance = new T();
			}

			return *m_Instance;
		}

	protected:
		Singleton() = default;

	private:
		static inline T* m_Instance{ nullptr };
	};
}

#endif // TETRISENGINE_SINGLETON_H