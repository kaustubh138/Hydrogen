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
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

	private:
		bool OnWindowClose(Events::WindowCloseEvent& e);
	
	public:
		Application();
		virtual ~Application();
	
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void OnEvent(Events::Event& e);
		void Run();
		
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	};

	Application* CreateApplication();
}

