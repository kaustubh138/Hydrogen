#pragma once

#ifdef H2_PLATFORM_WINDOWS

#include "Utils/Logger.hpp"

extern Hydrogen::Application* CreateApplication();

int main(int argc, char** argv)
{
	Hydrogen::Logger::Init();
	H2_CORE_WARN("Logger Initalized");
	H2_INFO("Info Log");

	Hydrogen::Application* app = Hydrogen::CreateApplication();
	app->Run();

	delete app;
	Hydrogen::Logger::Shutdown();
}

#endif