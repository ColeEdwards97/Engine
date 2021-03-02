#pragma once
#include "Engine/Math/Math.h"
#include <random>

namespace Engine
{

	namespace detail
	{
		
		/* GENERATORS */
		template<typename T>
		struct generator {
			using type = std::conditional_t<(sizeof(T) > 4), std::mt19937_64, std::mt19937>;
		};

		template<typename T>
		using generator_t = typename generator<T>::type;
		/* GENERATORS */


		/* DISTRIBUTIONS */
		template<typename T, typename = void>
		struct distribution;

		template<typename T>
		struct distribution<T, std::enable_if_t<std::is_integral_v<T>>> {
			using type = std::uniform_int_distribution;
		};

		template<typename T>
		struct distribution<T, std::enable_if_t<std::is_floating_point_v<T>>> {
			using type = std::uniform_real_distribution;
		};

		template<>
		struct distribution<bool> {
			using type = std::bernoulli_distribution;
		};

		template<typename T>
		using distribution_t = typename distribution<T>::type;
		/* DISTRIBUTIONS */



		/* RANDOM IMPLEMENTATIONS */
		template<typename T, typename = void>
		struct random_t;

		// general types types
		template<typename T>
		struct random_t<T, std::enable_if_t<(std::is_integral_v<T> || std::is_floating_point_v<T>)>>
		{
			[[nodiscard]] T operator()() {
				return this->operator()(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
			}

			[[nodiscard]] T operator()(T from, T to) {
				if (from > to) {
					T temp = from;
					from = to;
					to = from;
				}
				static std::random_device rd;
				static generator_t<T> generator(rd());
				distribution_t<T> distribution(from, to);
				return distribution(generator);
			}

		};

		// bools
		template<>
		struct random_t<bool>
		{
			[[nodiscard]] bool operator()(double p) {
				p = std::clamp(p, 0.0, 1.0);
				static std::random_device rd;
				static generator_t<bool> generator(rd());
				distribution_t<bool> distribution(p);
				return distribution(generator);
			}
		};

		// vectors
		template<glm::length_t L, typename T, glm::qualifier Q>
		struct random_t<glm::vec<L, T, Q>>
		{
			[[nodiscard]] constexpr glm::vec<L, T, Q> operator()() {
				return compute_rand_vector<L, T, Q, glm::detail::is_aligned<Q>::value>::call();
			}
			
			[[nodiscard]] constexpr glm::vec<L, T, Q> operator()(glm::vec<L, T, Q> const& from, glm::vec<L, T, Q> const& to) {
				return compute_rand_vector<L, T, Q, glm::detail::is_aligned<Q>::value>::call(from, to);
			}

		};


		// vector impls
		template<glm::length_t L, typename T, glm::qualifier Q, bool Aligned>
		struct compute_rand_vector
		{
			GLM_FUNC_QUALIFIER static glm::vec<L, T, Q> call()
			{
				return functor0<glm::vec, L, T, T, Q>::call(Random<T>);
			}
			GLM_FUNC_QUALIFIER static glm::vec<L, T, Q> call(glm::vec<L, T, Q> const& from, glm::vec<L, T, Q> const& to)
			{
				return glm::detail::functor2<glm::vec, L, T, Q>::call(Random<T>, from, to);
			}
		};

		// matrices
		template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
		struct random_t<glm::mat<C, R, T, Q>>
		{
			[[nodiscard]] constexpr glm::mat<C, R, T, Q> operator()() {
				return compute_rand_matrix<C, R, T, Q, glm::detail::is_aligned<Q>::value>::call();
			}

			[[nodiscard]] constexpr glm::mat<C, R, T, Q> operator()(glm::mat<C, R, T, Q> const& from, glm::mat<C, R, T, Q> const& to) {
				return compute_rand_matrix<C, R, T, Q, glm::detail::is_aligned<Q>::value>::call(from, to);
			}
		};
		
		// matrices impl
		template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q, bool Aligned>
		struct compute_rand_matrix
		{
			GLM_FUNC_QUALIFIER static glm::mat<C, R, T, Q> call()
			{
				glm::mat<C, R, T, Q> result{};
				for (glm::length_t i = 0; i < result.length(); ++i)
				{
					result[i] = functor0<glm::vec, C, T, T, Q>::call(Random<T>);
				}
				return result;
			}
			GLM_FUNC_QUALIFIER static glm::mat<C, R, T, Q> call(glm::mat<C, R, T, Q> const& from, glm::mat<C, R, T, Q> const& to)
			{
				glm::mat<C, R, T, Q> result{};
				for (glm::length_t i = 0; i < result.length(); ++i)
				{
					result[i] = glm::detail::functor2<glm::vec, C, T, Q>::call(Random<T>, from[i], to[i]);
				}
				return result;
			}
		};

		/* RANDOM IMPLEMENTATIONS */

	}

	
	// numeric limits
	template<typename T>
	auto Random() {
		static detail::random_t<T> rand{};
		return rand();
	}

	// in range
	template<typename T>
	auto Random(T from, T to) {
		static detail::random_t<T> rand{};
		return rand(from, to);
	}

	// probability
	bool Random(double p) {
		static detail::random_t<bool> rand{};
		return rand(p);
	}

}
