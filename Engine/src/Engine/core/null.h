#pragma once

#include <limits>

namespace Engine
{

	// BASE CASE. default construct
	template<typename T, typename = void>
	struct null_traits {
		static constexpr T value = T{};
	};
	
	// HELPER
	template<typename T>
	inline constexpr T null_traits_v = null_traits<T>::value;

	// DEFAULT OVERLOADS FOR PRIMITIVE TYPES
	template<typename T>
	struct null_traits<T, std::enable_if_t<std::is_integral_v<T>>> {
		static constexpr T value = std::numeric_limits<T>::max();
	};

	template<typename T>
	struct null_traits<T, std::enable_if_t<std::is_floating_point_v<T>>> {
		static constexpr T value = std::numeric_limits<T>::max();
	};

	template<>
	struct null_traits<bool> {
		static constexpr bool value = false;
	};

	
	// NULL_T
	struct null_t
	{

		template<typename T>
		[[nodiscard]] constexpr operator const T() const noexcept {
			return null_traits_v<T>;
		}

		template<typename T>
		[[nodiscard]] constexpr bool operator==(const T& other) const noexcept {
			return (other == static_cast<const T&>(*this));
		}
		template<typename T>
		[[nodiscard]] constexpr bool operator!=(const T& other) const noexcept {
			return (other != static_cast<const T&>(*this));
		}

		[[nodiscard]] constexpr bool operator==(const null_t&) const noexcept { return true; }
		[[nodiscard]] constexpr bool operator!=(const null_t&) const noexcept { return false; }

	};


	template<typename T>
	[[nodiscard]] constexpr bool operator==(const T& obj, const null_t& null) noexcept {
		return (null.operator==(obj));
	}
	
	template<typename T>
	[[nodiscard]] constexpr bool operator!=(const T& obj, const null_t& null) noexcept {
		return !(null == obj);
	}


	// NULL VARIABLE
	static constexpr null_t null{};

}