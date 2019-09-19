#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Anomaly
{
	class ANOMALY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define AE_CORE_TRACE(...) ::Anomaly::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AE_CORE_INFO(...)  ::Anomaly::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AE_CORE_WARN(...)  ::Anomaly::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AE_CORE_ERROR(...) ::Anomaly::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AE_CORE_FATAL(...) ::Anomaly::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define AE_TRACE(...) ::Anomaly::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AE_INFO(...)  ::Anomaly::Log::GetClientLogger()->info(__VA_ARGS__)
#define AE_WARN(...)  ::Anomaly::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AE_ERROR(...) ::Anomaly::Log::GetClientLogger()->error(__VA_ARGS__)
#define AE_FATAL(...) ::Anomaly::Log::GetClientLogger()->fatal(__VA_ARGS__)