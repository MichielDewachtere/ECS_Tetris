#ifndef TETRISENGINE_SUBJECT_H
#define TETRISENGINE_SUBJECT_H

#include <vector>

#include "Observer.h"

namespace monthly
{
	template <typename... Args>
	class Subject final
	{
	public:
		explicit Subject() = default;
		~Subject();

		Subject(const Subject& other) = delete;
		Subject& operator=(const Subject& rhs) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(Subject&& rhs) = delete;

		void AddObserver(Observer<Args...>* pObserver);
		bool HasObserver(Observer<Args...>* pObserver);
		void RemoveObserver(Observer<Args...>* pObserver);

		void Notify(Args... args) const;
		void Destroy();

		std::vector<Observer<Args ...>*> GetObservers() const { return m_pObservers; }

	private:
		mutable std::vector<Observer<Args ...>*> m_pObservers;
	};

	template<typename ...Args>
	inline Subject<Args...>::~Subject()
	{
		Destroy();
	}

	template<typename ...Args>
	inline void Subject<Args...>::AddObserver(Observer<Args...>* pObserver)
	{
		if (std::find(m_pObservers.begin(), m_pObservers.end(), pObserver) != m_pObservers.end())
		{
			return;
		}

		m_pObservers.push_back(pObserver);
	}

	template<typename ...Args>
	inline bool Subject<Args...>::HasObserver(Observer<Args...>* pObserver)
	{
		const auto it = std::ranges::find(m_pObservers, pObserver);

		if (it == m_pObservers.end())
			return false;

		return true;
	}

	template<typename ...Args>
	inline void Subject<Args...>::RemoveObserver(Observer<Args...>* pObserver)
	{
		if (m_pObservers.empty() == false)
		{
			m_pObservers.erase(
				std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver),
				m_pObservers.end()
			);
		}
	}

	template<typename ...Args>
	inline void Subject<Args...>::Notify(Args ...args) const
	{
		for (size_t i = 0; i < m_pObservers.size(); ++i)
		{
			const auto pObserver = m_pObservers[i];
			if (pObserver == nullptr)
				std::erase(m_pObservers, pObserver);

			pObserver->HandleEvent(args...);
		}
	}

	template <typename ... Args>
	void Subject<Args...>::Destroy()
	{
		for (auto& observer : m_pObservers)
		{
			if (observer == nullptr)
				continue;

			observer->OnSubjectDestroy();
		}
	}
}


#endif // TETRISENGINE_SUBJECT_H