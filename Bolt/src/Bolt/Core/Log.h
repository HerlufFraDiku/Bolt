#pragma once
#include "Bolt/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Bolt {
	class Log {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// core logging macros
#define BL_CORE_TRACE(...) ::Bolt::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BL_CORE_INFO(...)  ::Bolt::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BL_CORE_WARN(...)  ::Bolt::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BL_CORE_ERROR(...) ::Bolt::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BL_CORE_FATAL(...) ::Bolt::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// client logging macros
#define BL_TRACE(...) ::Bolt::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BL_INFO(...)  ::Bolt::Log::GetClientLogger()->info(__VA_ARGS__)
#define BL_WARN(...)  ::Bolt::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BL_ERROR(...) ::Bolt::Log::GetClientLogger()->error(__VA_ARGS__)
#define BL_FATAL(...) ::Bolt::Log::GetClientLogger()->fatal(__VA_ARGS__)