#pragma once

#include "engpch.h"

namespace Engine
{

	template<typename F>
	class FamilyID
	{
	public:

		template<typename T>
		static std::size_t Type() noexcept
		{
			static const std::size_t s_Value = Identifier();
			return s_Value;
		}

	private:

		static std::size_t Identifier() noexcept
		{
			static std::size_t s_Value = 0;
			return s_Value++;
		}
	};

	template<typename F, typename T>
	const std::size_t GetFamilyTypeID() { return FamilyID<F>().Type<T>(); }

}