#include "pch.hpp"

#include "Application.hpp"
#include "Events/KeyEvent.hpp"
#include "Utils/Logger.hpp"

namespace Hydrogen
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		Event::KeyPressed k(11, 0);
		H2_TRACE(k);
	}
}