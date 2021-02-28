#pragma once
#include "Engine/Math/Math.h"
#include <random>

namespace Engine
{
	
	// integer types
	template<typename T>
	GLM_FUNC_QUALIFIER typename std::enable_if<std::is_integral<T>::value, T>::type
		Random(T range_from, T range_to) {
		{
			ENGINE_CORE_ASSERT((range_from <= range_to), "Invalid range");
			// swap values if ranges are reversed
			if (range_from > range_to)
			{
				T temp = range_from;
				range_from = range_to;
				range_to = temp;
			}
		}
		static std::random_device randomDevice;
		static std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<T> distr(range_from, range_to);
		return distr(generator);
	}

	// floating point types
	template<typename T>
	GLM_FUNC_QUALIFIER typename std::enable_if<std::is_floating_point<T>::value, T>::type
		Random(T range_from, T range_to)
	{
		ENGINE_CORE_ASSERT((range_from <= range_to), "Invalid range");
		// swap values if ranges are reversed
		if (range_from > range_to)
		{
			T temp = range_from;
			range_from = range_to;
			range_to = temp;
		}
		static std::random_device randomDevice;
		static std::mt19937 generator(randomDevice());
		std::uniform_real_distribution<T> distr(range_from, range_to);
		return distr(generator);
	}
	

	// glm vectors
	template<glm::length_t L, typename T, glm::qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR glm::vec<L, T, Q> Random(glm::vec<L, T, Q> const& range_from, glm::vec<L, T, Q> const& range_to)
	{
		return compute_rand_vector<L, T, Q, glm::detail::is_aligned<Q>::value>::call(range_from, range_to);
	}

	template<glm::length_t L, typename T, glm::qualifier Q, bool Aligned>
	struct compute_rand_vector
	{
		GLM_FUNC_QUALIFIER static glm::vec<L, T, Q> call(glm::vec<L, T, Q> const& range_from, glm::vec<L, T, Q> const& range_to)
		{
			return glm::detail::functor2<glm::vec, L, T, Q>::call(Random<T>, range_from, range_to);
		}
	};

	// glm matrices
	template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR glm::mat<C, R, T, Q> Random(glm::mat<C, R, T, Q> const& range_from, glm::mat<C, R, T, Q> const& range_to)
	{
		return compute_rand_matrix<C, R, T, Q, glm::detail::is_aligned<Q>::value>::call(range_from, range_to);
	}

	template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q, bool Aligned>
	struct compute_rand_matrix
	{
		GLM_FUNC_QUALIFIER static glm::mat<C, R, T, Q> call(glm::mat<C, R, T, Q> const& range_from, glm::mat<C, R, T, Q> const& range_to)
		{
			glm::mat<C, R, T, Q> result;
			for (glm::length_t i = 0; i < result.length(); ++i)
			{
				result[i] = glm::detail::functor2<glm::vec, C, T, Q>::call(Random<T>, range_from[i], range_to[i]);
			}
			return result;
		}
	};



}
