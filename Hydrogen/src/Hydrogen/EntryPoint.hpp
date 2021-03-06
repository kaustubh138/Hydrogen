#pragma once

#ifdef H2_PLATFORM_WINDOWS

#include "Utils/Logger.hpp"

extern Hydrogen::Application* CreateApplication();

int main(int argc, char** argv)
{
	Hydrogen::Logger::Init();
	H2_CORE_INFO("Logger Initalized");

	Hydrogen::Application* app = Hydrogen::CreateApplication();
	app->Run();

	delete app;
	Hydrogen::Logger::Shutdown();
}

#endif