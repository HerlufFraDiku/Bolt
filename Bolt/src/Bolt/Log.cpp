#include "Log.h"

namespace Bolt {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		// set pattern to: Timestamp loggername message
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Create core logger
		s_CoreLogger = spdlog::stdout_color_mt("BOLT");
		s_CoreLogger->set_level(spdlog::level::trace);

		// Create client logger
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}