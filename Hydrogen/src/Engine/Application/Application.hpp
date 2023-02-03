#pragma once

#include "Core.hpp"

#include "Timestep.hpp"
#include "Engine/Events/Event.hpp"
#include "Engine/Events/WindowEvent.hpp"
#include "Engine/Window.hpp"
#include "Layers/LayerStack.hpp"
#include "ImGui/ImGuiLayer.hpp"

namespace Hydrogen
{
	class H2_API Application
	{
	private:
		static Application* s_Instance;
		float m_LastFrameTime;

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		bool m_Running = true;
		bool m_Minimized = true;

	private:
		bool OnWindowClose(Events::WindowCloseEvent& e);
		bool OnWindowResize(Events::WindowResizeEvent& e);

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

