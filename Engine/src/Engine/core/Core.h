#pragma once

#include <memory>

#ifdef ENG_PLATFORM_WINDOWS
#else
	#error Engine currently only supports Windows!
#endif

#ifdef ENG_DEBUG
	#define ENG_ENABLE_ASSERTS
#endif // ENG_DEBUG

#ifdef ENG_ENABLE_ASSERTS
	#define ENGINE_ASSERT(x, ...) { if(!(x)) { ENGINE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ENGINE_CORE_ASSERT(x, ...) { if(!(x)) { ENGINE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ENGINE_ASSERT(x, ...)
	#define ENGINE_CORE_ASSERT(x, ...)
#endif // ENG_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define ENG_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }


namespace Engine
{
	typedef uint64_t EntityID;

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... ARGS>
	constexpr Scope<T> CreateScope(ARGS&& ... args)
	{
		return std::make_unique<T>(std::forward<ARGS>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... ARGS>
	constexpr Ref<T> CreateRef(ARGS&& ... args)
	{
		return std::make_shared<T>(std::forward<ARGS>(args)...);
	}

}