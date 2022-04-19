#pragma once

#include "Core.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hydrogen
{
	class H2_API Logger
	{
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	
	public: 
		static void Init();
		static void Shutdown();
	
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}


// Engine Log Macros
#define H2_CORE_TRACE(...)	::Hydrogen::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define H2_CORE_INFO(...)	::Hydrogen::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define H2_CORE_WARN(...)	::Hydrogen::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define H2_CORE_ERROR(...)	::Hydrogen::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define H2_CORE_FATAL(...)	::Hydrogen::Logger::GetEngineLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define H2_TRACE(...)	::Hydrogen::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define H2_INFO(...)	::Hydrogen::Logger::GetClientLogger()->info(__VA_ARGS__)
#define H2_WARN(...)	::Hydrogen::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define H2_ERROR(...)	::Hydrogen::Logger::GetClientLogger()->error(__VA_ARGS__)
#define H2_FATAL(...)	::Hydrogen::Logger::GetClientLogger()->fatal(__VA_ARGS__)
