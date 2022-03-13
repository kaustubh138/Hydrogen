#pragma once

#ifdef H2_PLATFORM_WINDOWS

extern Hydrogen::Application* CreateApplication();

int main(int argc, char** argv)
{
	Hydrogen::Application* app = Hydrogen::CreateApplication();
	app->Run();
	delete app;
}

#endif