#pragma once

#include <spdlog/spdlog.h>

namespace Engine {

	class Log {

	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_clientLogger; }

	private:
		static Ref<spdlog::logger> s_coreLogger;		
		static Ref<spdlog::logger> s_clientLogger;

	};

}

// Core log macros
#define ENGINE_CORE_TRACE(...) ::Engine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...) ::Engine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_CORE_WARN(...) ::Engine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...) ::Engine::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define ENGINE_TRACE(...) ::Engine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENGINE_INFO(...) ::Engine::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...) ::Engine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...) ::Engine::Log::GetClientLogger()->error(__VA_ARGS__)
