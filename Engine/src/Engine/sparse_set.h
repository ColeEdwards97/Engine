#pragma once

#include "engpch.h"
#include "Engine/Core/null.h"

namespace Engine
{

	template<typename T, size_t block_size = 1024>
	class sparse_set
	{
		static_assert((std::is_unsigned_v<T>), "sparse_set can only contain unsigned types");
		static_assert((std::is_integral_v<T>), "sparse_set can only contain integral types");
		static_assert(((block_size & (block_size - 1)) == 0), "block_size must be a power of 2");
		
	protected:

		using packed_type = T;
		using sparse_type = std::unique_ptr<T[]>;
		using size_type = size_t;

		static constexpr size_type items_per_block = block_size / sizeof(T);


	public:

		[[nodiscard]] size_type size() const {
			return _packed.size();
		}

		[[nodiscard]] size_type capacity() const {
			return _packed.capacity();
		}

		[[nodiscard]] size_type extent() const {
			return _sparse.size() * items_per_block;
		}


		[[nodiscard]] bool contains(const packed_type item) const {
			size_type idx = index(item);
			return (idx < _sparse.size() && _sparse[idx] && _sparse[idx][offset(item)] != null);
		}

		void emplace(const packed_type item) {
			if (contains(item)) return;
			assure(index(item))[offset(item)] = packed_type{ static_cast<packed_type>(_packed.size()) };
			_packed.push_back(item);
		}

		void remove(const packed_type item) {
			if (!contains(item)) return;
			auto& remove = _sparse[index(item)][offset(item)];
			const auto pos = to_integral(remove);
			const auto back = _packed.back();

			_sparse[index(back)][offset(back)] = remove;
			_packed[pos] = back;

			remove = null;

			_packed.pop_back();
			swap_and_pop(pos);
		}


	protected:
		
		[[nodiscard]] size_type to_integral(const packed_type item) const {
			return size_type{ item };
		}

		[[nodiscard]] size_type index(const packed_type item) const {
			return (to_integral(item) / items_per_block);
		}

		[[nodiscard]] size_type offset(const packed_type item) const {
			return (to_integral(item) & (items_per_block - 1));
		}

		[[nodiscard]] sparse_type& assure(const size_type position) {
			if (position >= _sparse.size()) {
				_sparse.resize(position + 1);
			}
			if (!_sparse[position]) {
				_sparse[position].reset(new packed_type[items_per_block]);

				for (auto* first = _sparse[position].get(), *last = first + items_per_block; first != last; ++first) {
					*first = null;
				}
			}
			return _sparse[position];
		}

		virtual void swap_and_pop(const size_type pos) {}
		

	private:
		std::vector<packed_type> _packed;
		std::vector<sparse_type> _sparse;

	};

}