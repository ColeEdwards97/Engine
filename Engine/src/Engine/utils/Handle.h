#pragma once

#include "Engine/Core/Core.h"

namespace Engine
{

	template<typename T, typename value_type = uint64_t>
	class Handle
	{

		static_assert(sizeof(value_type) <= sizeof(size_t), "value_type is too large for this system");

	public:

		[[nodiscard]] static value_type AcquireHandle()
		{
			return s_Next++;
		}

		static void FreeHandle(value_type handle)
		{
			return;
		}

	private:
		static constexpr value_type MAX_ID { std::numeric_limits<value_type>::max() };
		static constexpr value_type MIN_ID { std::numeric_limits<value_type>::min() };
		static value_type s_Next;

	};
	template<typename T, typename value_type>
	value_type Handle<T, value_type>::s_Next = 0;

}