#pragma once

#include "engpch.h"

namespace Engine
{

	template<typename T>
	class SparseSet
	{

		static_assert(std::is_unsigned<T>::value, "SparseSet must constain an unsigned type");

	public:

		SparseSet()
		{
			Resize(1000000);
		}
		
		SparseSet(size_t maxSize)
		{
			Resize(maxSize);
		}
		
		void Resize(size_t value)
		{
			if (value > m_Sparse.size())
			{
				m_Sparse.resize(value, nullptr);
				m_Dense.reserve(value);
				m_Dense.clear();
			}
		}
		
		bool Has(const T& value)
		{
			return (value < m_Sparse.size()) &&
				m_Sparse[value] != nullptr;
		}

		void Insert(const T& value)
		{
			if (!Has(value))
			{
				m_Dense.push_back(value);
				m_Sparse[value] = &m_Dense.back();
			}
		}

		void Erase(const T& value)
		{
			if (Has(value))
			{
				*(m_Sparse[value]) = m_Dense.back();
				m_Sparse[m_Dense.back()] = m_Sparse[value];
				m_Dense.erase(m_Dense.end() - 1);
				m_Sparse[value] = nullptr;
			}
		}

		void Clear()
		{
			m_Sparse.resize(m_Sparse.size(), nullptr);
			m_Dense.reserve(m_Sparse.size());
			m_Dense.clear();
		}


		/* ITERATOR */
		using iterator = typename std::vector<T>::const_iterator;
		using const_iterator = typename std::vector<T>::const_iterator;

		iterator begin() { return m_Dense.begin(); }
		const_iterator begin() const { return m_Dense.begin(); }

		iterator end() { return m_Dense.end(); }
		const_iterator end() const { return m_Dense.end(); }
		

	public:

		std::vector<T*> m_Sparse;
		std::vector<T> m_Dense;

	};

}

