#pragma once

#include "engpch.h"

#include "Engine/SparseSet.h"

namespace Engine
{

	template<typename K, typename V>
	class SparseMap
	{

	public:

		SparseMap()
		{
			Resize(1000000);
		}

		SparseMap(size_t maxSize)
		{
			Resize(maxSize);
		}

		void Resize(size_t size)
		{
			if (size > m_SparseValue.size())
			{
				m_SparseValue.resize(size, nullptr);
				m_DenseValue.reserve(size);
				m_DenseValue.clear();

				m_SparseSet.Resize(size);
			}
		}


		bool Has(const K& key)
		{
			return m_SparseSet.Has(key) && m_SparseValue[key] != nullptr;
		}

		void Insert(const K& key, const V& value)
		{
			if (!Has(key))
			{
				m_DenseValue.push_back(value);
				m_SparseValue[key] = &m_DenseValue.back();

				m_SparseSet.Insert(key);
			}
		}

		void Erase(const K& key)
		{
			if (Has(key))
			{
				*(m_SparseValue[key]) = m_DenseValue.back();
				m_SparseValue[m_SparseSet.m_Dense.back()] = m_SparseValue[key];
				m_DenseValue.erase(m_DenseValue.end() - 1);
				m_SparseValue[key] = nullptr;

				m_SparseSet.Erase(key);
			}
		}

		void Clear()
		{
			m_SparseValue.resize(m_SparseValue.size(), nullptr);
			m_DenseValue.reserve(m_SparseValue.size());
			m_DenseValue.clear();
		}

		V& Get(const K& key)
		{
			if (!Has(key))
			{
				Insert(key, V());
			}
			return *(m_SparseValue[key]);
		}

		void Set(const K& key, const V& value)
		{
			if (Has(key))
			{
				*(m_SparseValue[key]) = value;
			}
			else 
			{
				Insert(key, value);
			}
		}


	private:

		SparseSet<K> m_SparseSet;
		std::vector<V*> m_SparseValue;
		std::vector<V> m_DenseValue;

	};

}