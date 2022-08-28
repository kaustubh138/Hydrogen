#pragma once

#include "Core.hpp"

#include "Engine/Events/Event.hpp"
#include "Engine/Events/WindowEvent.hpp"
#include "Engine/Window.hpp"
#include "Layers/LayerStack.hpp"
#include "Engine/Renderer/Buffer.hpp"

#include "Renderer/Shader/Shader.hpp"

namespace Hydrogen
{
	class H2_API Application
	{
	private:
		static Application* s_Instance;

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

		unsigned int m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

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

