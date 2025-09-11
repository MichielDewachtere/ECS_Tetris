#ifndef TETRISENGINE_DYNAMICBITSET_H
#define TETRISENGINE_DYNAMICBITSET_H

#include <stdexcept>
#include <string>
#include <vector>

#include "EngineConcepts.h"

namespace monthly
{
	template<unsigned_integer T = uint8_t>
	class DynamicBitset final
	{
	public:
		class Reference
		{
			friend DynamicBitset<T>;
		public:
			~Reference() = default;

			Reference& operator=(bool value)
			{
				m_pBitset->Set(m_Pos, value);
				return *this;
			}
			Reference& operator=(const Reference& bitRef)
			{
				m_pBitset->Set(m_Pos, static_cast<bool>(bitRef));
				return *this;
			}

			Reference& Flip()
			{
				m_pBitset->Flip(m_Pos);
				return *this;
			}

			bool operator~() const
			{
				return !m_pBitset->Set(m_Pos);
			}

			operator bool() const
			{
				return m_pBitset->Test(m_Pos);
			}

		private:
			Reference() : m_pBitset(nullptr), m_Pos() {}
			Reference(DynamicBitset<T>& bitset, const size_t pos) : m_pBitset(&bitset), m_Pos(pos) {}

			DynamicBitset<T>* m_pBitset;
			size_t m_Pos;
		};

		inline DynamicBitset(size_t size)
		{
			size_t vectorSize = GetVectorSize(size);
			m_Data = std::vector<T>(vectorSize, 0);
			m_Size = m_Data.size() * bits_per_type;
		}
		inline DynamicBitset(const std::string& data)
		{
			size_t vectorSize = GetVectorSize(data.size());
			m_Data = std::vector<T>(vectorSize, 0);
			m_Size = m_Data.size() * bits_per_type;

			int vectorPos = -1;
			for (size_t i = 0; i < data.size(); ++i)
			{
				bool value = '0' - data[i];
				if (!value)
				{
					continue;
				}

				size_t j = i % bits_per_type;
				if (j == 0)
				{
					++vectorPos;
				}

				m_Data[vectorPos] += 1 << j;
			}
		}

		~DynamicBitset() = default;

		//DynamicBitset(const DynamicBitset& other) = delete;
		//DynamicBitset& operator=(const DynamicBitset& rhs) = delete;
		//DynamicBitset(DynamicBitset&& other) = delete;
		//DynamicBitset& operator=(DynamicBitset&& rhs) = delete;

		bool operator[](size_t pos) const
		{
			return m_Size <= pos ? false : Test(pos);
		}

		Reference operator[](const size_t pos)
		{
			if (m_Size <= pos)
			{
				throw std::runtime_error("Bitset index out of range");
			}

			return Reference(*this, pos);
		}

		void Set()
		{
			// TODO: Is -1 always going to loop?
			for (auto& e : m_Data)
			{
				e = static_cast<T>(-1);
			}
		}
		void Set(size_t pos, bool value = true)
		{
			if (pos >= m_Size)
			{
				Resize(pos);
			}

			auto& selected = m_Data[pos / bits_per_type];
			auto bit = static_cast<T>(1) << (pos % bits_per_type);

			if (value)
			{
				selected |= bit;
			}
			else
			{
				selected &= ~bit;
			}
		}
		void Reset()
		{
			for (auto& e : m_Data)
			{
				e = 0;
			}
		}
		void Reset(size_t pos)
		{
			if (pos >= m_Size)
			{
				return;
			}

			Set(pos, false);
		}
		void Flip(size_t pos)
		{
			if (pos >= m_Size)
			{
				Resize(pos);
			}

			m_Data[pos / bits_per_type] ^= static_cast<T>(1) << (pos % bits_per_type);
		}

		bool Test(size_t pos)
		{
			if (pos >= m_Size)
			{
				return false;
			}

			T data = m_Data[pos / bits_per_type];
			data >>= pos % bits_per_type;
			return data - (data - 1);
		}
		bool All()
		{
			for (auto e : m_Data)
			{
				if (e != ~static_cast<T>(0))
					return false;
			}

			return true;
		}
		bool Any()
		{
			for (auto e : m_Data)
			{
				if (e != 0)
					return true;
			}

			return false;
		}
		bool None()
		{
			for (auto e : m_Data)
			{
				if (e != 0)
					return false;
			}

			return true;
		}

		int Count()
		{
			int count = 0;
			for (auto e : m_Data)
			{
				count += std::popcount(e);
			}

			return count;
		}

		std::string ToString()
		{
			int size = m_Data.size() * bits_per_type;

			std::string s;
			s.reserve(size);
			for (int i = size - 1; i >= 0; --i)
			{
				s.push_back(Test(i));
			}

			return s;
		}

		void Resize(size_t newSize)
		{
			size_t vectorSize = GetVectorSize(newSize);
			if (vectorSize == m_Data.size())
			{
				return;
			}

			m_Data.resize(vectorSize);
			m_Size = vectorSize * bits_per_type;
		}

	private:
		std::vector<T> m_Data;
		size_t m_Size;

		static constexpr int bits_per_byte = 8;
		static constexpr int bits_per_type = sizeof(T) * bits_per_byte;

		static inline size_t GetVectorSize(size_t size)
		{
			return (size + bits_per_type - 1) / bits_per_type;
		}
	};
}

#endif // TETRISENGINE_DYNAMICBITSET_H