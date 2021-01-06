#pragma once

#include "engpch.h"

namespace Engine
{

	template<typename ...T>
	class SparseSet;

	template<typename T>
	class SparseSet<T>
	{

		static_assert(std::is_unsigned<T>::value, "SparseSet must constain an unsigned type");

	public:

		/* CONSTRUCTORS */
		SparseSet()
		{
			Resize(64);
		}
		
		SparseSet(size_t maxSize)
		{
			Resize(maxSize);
		}
		

		/* OPERATIONS */
		void Resize(size_t size)
		{
			if (size > m_Sparse.size())
			{
				m_Sparse.resize(size, nullptr);
				m_Dense.reserve(size);
				m_Dense.clear();
			}
		}
		
		bool Has(const T& value)
		{
			return (value < m_Sparse.size()) &&
				m_Sparse[value] != nullptr;
		}

		T& Get(const T& value)
		{
			if (!Has(value))
			{
				Insert(value);
			}
			return *(m_Sparse[value]);
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
		using iterator = typename std::vector<T>::iterator;
		using const_iterator = typename std::vector<T>::const_iterator;
		using reverse_iterator = typename std::vector<T>::reverse_iterator;
		using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

		iterator begin() { return m_Dense.begin(); }
		iterator end() { return m_Dense.end(); }
		const_iterator begin() const { return m_Dense.begin(); }
		const_iterator end() const { return m_Dense.end(); }
		reverse_iterator rbegin() { return m_Dense.rbegin(); }
		reverse_iterator rend() { return m_Dense.rend(); }
		const_reverse_iterator rbegin() const { return m_Dense.rbegin(); }
		const_reverse_iterator rend() const { return m_Dense.rend(); }

	public:

		std::vector<T*> m_Sparse;
		std::vector<T> m_Dense;

	};


	template<typename K, typename V>
	class SparseSet<K, V>
	{

		static_assert(std::is_unsigned<K>::value, "SparseSet must use an unsigned type for keys");

	public:

		/* CONSTRUCTORS */
		SparseSet()
		{
			Resize(64);
		}

		SparseSet(size_t maxSize)
		{
			Resize(maxSize);
		}


		/* OPERATIONS */
		void Resize(size_t size)
		{
			if (size > m_Sparse.size())
			{
				m_Sparse.resize(size, nullptr);
				m_Dense.reserve(size);
				m_Dense.clear();
			}
		}

		bool Has(const K& key)
		{
			return (key < m_Sparse.size()) &&
				m_Sparse[key] != nullptr;
		}

		V& Get(const K& key)
		{
			if (!Has(key))
				Insert(key, nullptr);
			return m_DenseValue[*(m_Sparse[key])];
		}

		void Insert(const K& key, const V& value)
		{
			if (!Has(key))
			{
				m_Dense.push_back((K)m_Dense.size());
				m_DenseValue.push_back(value);
				m_Sparse[key] = &m_Dense.back();
			}
		}

		void Erase(const K& key)
		{
			if (Has(key))
			{
				K sparseVal = *(m_Sparse[key]);
				m_DenseValue.erase(m_DenseValue.begin() + sparseVal, m_DenseValue.begin() + sparseVal + 1);
				
				*(m_Sparse[key]) = m_Dense.back();
				m_Sparse[m_Dense.back()] = m_Sparse[key];
				m_Dense.erase(m_Dense.end() - 1);
				m_Sparse[key] = nullptr;
			}
		}

		void Erase(const K& key, const V& value)
		{
			if (Has(key))
			{
				if ((*(m_Sparse[key])) == value)
				{
					Erase(key);
				}
			}
		}

		void Clear()
		{
			m_Sparse.resize(m_Sparse.size(), nullptr);
			m_Dense.reserve(m_Sparse.size());
			m_Dense.clear();
		}


		/* ITERATOR */
		using iterator = typename std::vector<V>::iterator;
		using const_iterator = typename std::vector<V>::const_iterator;
		using reverse_iterator = typename std::vector<V>::reverse_iterator;
		using const_reverse_iterator = typename std::vector<V>::const_reverse_iterator;

		iterator begin() { return m_DenseValue.begin(); }
		iterator end() { return m_DenseValue.end(); }
		const_iterator begin() const { return m_DenseValue.begin(); }
		const_iterator end() const { return m_DenseValue.end(); }
		reverse_iterator rbegin() { return m_DenseValue.rbegin(); }
		reverse_iterator rend() { return m_DenseValue.rend(); }
		const_reverse_iterator rbegin() const { return m_DenseValue.rbegin(); }
		const_reverse_iterator rend() const { return m_DenseValue.rend(); }

	private:

		std::vector<K*> m_Sparse;
		std::vector<K> m_Dense;
		std::vector<V> m_DenseValue;

	};

}

