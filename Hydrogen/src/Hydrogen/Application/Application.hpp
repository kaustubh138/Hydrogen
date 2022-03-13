#pragma once

#include "Core.hpp"

namespace Hydrogen
{
	class H2_API Application
	{
	public:
		Application();
		virtual ~Application();
	
		void Run();
	};

	Application* CreateApplication();
}

