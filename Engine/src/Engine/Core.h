#pragma once

#ifdef ENG_PLATFORM_WINDOWS
	#ifdef ENGINE_BUILD_DLL
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Engine currently only supports Windows!
#endif


#ifdef ENG_ENABLE_ASSERTS
	#define ENGINE_ASSERT(x, ...) { if(!(x)) { ENGINE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ENGINE_CORE_ASSERT(x, ...) {if(!(x)) { ENGINE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ENGINE_ASSERT(x, ...)
	#define ENGINE_CORE_ASSERT(x, ...)
#endif // ENG_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define ENG_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }