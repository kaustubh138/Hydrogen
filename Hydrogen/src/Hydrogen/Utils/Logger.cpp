#include "Logger.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hydrogen
{
	std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;

	void Logger::Init()
	{
		/*
		* Refrence: https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
		* %^	  : start color range
		*	[%T]  : time format (HH:MM:SS), equivalent to %H:%M:%S
		*	 %n	  : logger name
		*	 %v	  : actual text to log
		* %$	  : end color range
		*/
		spdlog::set_pattern("%^[%T] %n: %v%$");
	
		s_EngineLogger = spdlog::stdout_color_mt("HYDROGEN");
		s_EngineLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	void Logger::Shutdown()
	{
		s_EngineLogger.reset();
		spdlog::drop_all();
	}
}
