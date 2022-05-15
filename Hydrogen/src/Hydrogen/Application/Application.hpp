#pragma once

#include "Core.hpp"

#include "Hydrogen/Events/Event.hpp"
#include "Hydrogen/Events/WindowEvent.hpp"
#include "Hydrogen/Window.hpp"
#include "Layers/LayerStack.hpp"

namespace Hydrogen
{
	class H2_API Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

	public:
		Application();
		virtual ~Application();
	
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void OnEvent(Event::Event& e);
		void Run();
		bool OnWindowClose(Event::WindowCloseEvent& e);
	};

	Application* CreateApplication();
}

