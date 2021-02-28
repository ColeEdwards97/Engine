#pragma once

#include "engpch.h"

namespace Engine
{

	template<class T>
	class free_list
	{
	private:
		union free_element;

	public:

		// default constructor
		free_list() : _first_free((size_t)-1) {}

		// insert element into list
		size_t insert(const T& element)
		{
			if (_first_free != (size_t)-1)
			{
				const size_t index = _first_free;
				_first_free = _data[_first_free].next;
				data[index].element = element;
				return index;
			}
			else
			{
				free_element e;
				e.element = element;
				_data.push_back(e);
				return static_cast<size_t>(_data.size());
			}
		}

		size_t size()
		{
			return _data.size();
		}

		// erase element at index from list
		void erase(size_t index)
		{
			_data[index].next = _first_free;
			_first_free = index;
		}

		// clear free list
		void clear()
		{
			_data.clear();
			_first_free = (size_t)-1;
		}

		// is the free list empty
		[[no_discard]] bool empty()
		{
			return _data.size() == 0 && _first_free == (size_t)-1;
		}

		// operator overloads
		T& operator[](size_t index) { return _data[index].element; }
		const T& operator[](size_t index) const { return _data[index].element; }


	private:
		union free_element
		{
			T element;
			size_t next;
		};
		std::vector<free_element> _data;
		size_t _first_free;

	};

}
