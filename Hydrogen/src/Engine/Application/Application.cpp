#include "pch.hpp"

#include "Application.hpp"
#include "Engine/Utils/Logger.hpp"
#include "Engine/Events/WindowEvent.hpp"
#include "Engine/Window.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Renderer/Buffer.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/RenderCommand.hpp"

#include "Engine/Events/MouseEvent.hpp"
#include <GLFW/glfw3.h>

namespace Hydrogen
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		H2_CORE_ASSERT(!s_Instance, "An application instance already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Events::Event& e)
	{
		Events::EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<Events::WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			// H2_CORE_INFO(e);
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* l : m_LayerStack)
				l->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(Events::WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}