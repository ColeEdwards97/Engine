#pragma once

#include <random>

namespace Engine
{
	template<typename T>
	T Random(T range_from, T range_to) {
		std::random_device randomDevice;
		std::mt19937 generator(randomDevice());
		std::uniform_int_distribution<T> distr(range_from, range_to);
		return distr(generator);
	}
}
