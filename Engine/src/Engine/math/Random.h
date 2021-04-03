#pragma once
#include "Engine/Math/Math.h"
#include <random>

namespace Engine
{
	namespace detail
	{
		
		// generators
		template<typename T>
		struct generator {
			using type = std::conditional_t<(sizeof(T) > 4), std::mt19937_64, std::mt19937>;
		};

		template<typename T>
		using generator_t = typename generator<T>::type;

		// distributions
		template<typename T, typename = void>
		struct distribution;

		template<typename T>
		struct distribution<T, std::enable_if_t<std::is_integral_v<T>>> {
			using type = std::uniform_int_distribution<T>;
		};

		template<typename T>
		struct distribution<T, std::enable_if_t<std::is_floating_point_v<T>>> {
			using type = std::uniform_real_distribution<T>;
		};

		template<>
		struct distribution<bool> {
			using type = std::bernoulli_distribution;
		};

		template<typename T>
		using distribution_t = typename distribution<T>::type;

		// random functions
		template<typename T, typename = void>
		struct random_func;

		template<typename T>
		struct random_func<T, std::enable_if_t<std::is_arithmetic_v<T>>>
		{
			[[nodiscard]] T next() {
				return next_in_range(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
			}
			[[nodiscard]] T next_in_range(T min, T max = std::numeric_limits<T>::max()) {
				static std::random_device rd;
				static generator_t<T> gen(rd());
				distribution_t<T> distr(std::min(min, max), std::max(min, max));
				return distr(gen);
			}

		};

		template<>
		struct random_func<bool> 
		{
			[[nodiscard]] bool probability(double p = 0.5) 
			{
				p = std::clamp(p, 0.0, 1.0);
				static std::random_device rd;
				static generator_t<bool> gen(rd());
				distribution_t<bool> distr(p);
				return distr(gen);
			}
		};

		// free funcs for glm::functor
		template<typename T>
		T random(T min, T max) {
			return random_func<T>{}.next_in_range(min, max);
		}

		bool random(double p) {
			return random_func<bool>{}.probability(p);
		}

		// vectors
		template<template<glm::length_t, typename, glm::qualifier> class vec, glm::length_t L, typename T, glm::qualifier Q>
		struct random_func<vec<L, T, Q>> 
		{
			[[nodiscard]] vec<L, T, Q> next() {
				return next_in_range(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
			}
			[[nodiscard]] vec<L, T, Q> next_in_range(T min, T max = std::numeric_limits<T>::max()) {
				return compute_rand_vector<L, T, Q, glm::detail::is_aligned<Q>::value>::call(vec<L, T, Q>{ min }, vec<L, T, Q>{ max });
			}
			[[nodiscard]] vec<L, T, Q> next_in_range(vec<L, T, Q> const& min, vec<L, T, Q> const& max) {
				return compute_rand_vector<L, T, Q, glm::detail::is_aligned<Q>::value>::call(min, max);
			}
		};

		template<template<glm::length_t, typename, glm::qualifier> class vec, glm::length_t L, glm::qualifier Q>
		struct random_func<vec<L, bool, Q>> 
		{
			[[nodiscard]] vec<L, bool, Q> probability(double p = 0.5) {
				return compute_rand_vector<L, bool, Q, glm::detail::is_aligned<Q>::value>::call(p);
			}
		};

		template<glm::length_t L, typename T, glm::qualifier Q, bool Aligned>
		struct compute_rand_vector
		{
			GLM_FUNC_QUALIFIER static glm::vec<L, T, Q> call(glm::vec<L, T, Q> const& min, glm::vec<L, T, Q> const& max)
			{
				return glm::detail::functor2<glm::vec, L, T, Q>::call(random<T>, min, max);
			}
			GLM_FUNC_QUALIFIER static glm::vec<L, T, Q> call(double p)
			{
				return glm::detail::functor1<glm::vec, L, T, double, Q>::call(random, glm::vec<L, double, Q>{ p });
			}
		};

		// matrices
		template<template<glm::length_t, glm::length_t, typename, glm::qualifier> class mat, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
		struct random_func<mat<C, R, T, Q>> 
		{
			[[nodiscard]] mat<C, R, T, Q> next() {
				return next_in_range(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
			}
			[[nodiscard]] mat<C, R, T, Q> next_in_range(T min, T max) {
				return compute_rand_matrix<C, R, T, Q>::call(
					glm_helper::glm_mat<mat<C, R, T, Q>>::all(min),
					glm_helper::glm_mat<mat<C, R, T, Q>>::all(max)
				);
			}
			[[nodiscard]] mat<C, R, T, Q> next_in_range(mat<C, R, T, Q> const& min, mat<C, R, T, Q> const& max) {
				return compute_rand_matrix<C, R, T, Q>::call(min, max);
			}
		};

		template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
		struct compute_rand_matrix
		{
			GLM_FUNC_QUALIFIER static glm::mat<C, R, T, Q> call(glm::mat<C, R, T, Q> const& min, glm::mat<C, R, T, Q> const& max)
			{
				glm::mat<C, R, T, Q> ret{};
				for (glm::length_t i = 0; i < C; ++i)
				{
					ret[i] = glm::detail::functor2<glm::vec, R, T, Q>::call(random<T>, min[i], max[i]);
				}
				return ret;
			}
		};

		// seeded random functions
		template<typename T, typename = void>
		struct seeded_random_func;

		template<typename T>
		struct seeded_random_func<T> 
		{};

	}

	// interface
	template<typename T>
	using random_t = detail::random_func<T>;

	template<typename T>
	using srandom_t = detail::seeded_random_func<T>;


}
