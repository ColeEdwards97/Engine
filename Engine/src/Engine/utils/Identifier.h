#pragma once

#include "Engine/Core/Core.h"

namespace Engine
{
	
	// GENERIC ID

	template<typename value_type = std::size_t>
	class Identifier
	{

		static_assert(sizeof(value_type) <= sizeof(std::size_t), "value_type is too large for this system");
		static_assert(std::is_integral_v<value_type>, "value_type must be an integral type");

	public:

		template<typename T>
		[[nodiscard]] static value_type Get() {
			static value_type s_Identifier = MIN_ID;
			return s_Identifier++;
		}

	private:
		static constexpr value_type MAX_ID{ std::numeric_limits<value_type>::max() };
		static constexpr value_type MIN_ID{ std::numeric_limits<value_type>::min() };
	};



	// TYPE ID
	template<typename T, typename value_type>
	struct TypeIdentifier
	{
		[[nodiscard]] static value_type Get() {
			static const value_type s_Identifier = Identifier<value_type>::template Get<T>();
			return s_Identifier;
		}
	};
	template<typename T, typename value_type>
	static value_type GetTypeIdentifier() { return TypeIdentifier<T, value_type>::Get(); }

	

	// FAMILY TYPE ID
	template<typename Family, typename value_type>
	struct FamilyTypeIdentifier
	{
		template<typename T>
		[[nodiscard]] static value_type Get() {
			static const value_type s_Identifier = Identifier<value_type>::template Get<Family>();
			return s_Identifier;
		}
	};
	template<typename Family, typename T, typename value_type>
	static value_type GetFamilyTypeIdentifier() { return FamilyTypeIdentifier<Family, value_type>::template Get<T>(); }

}