#include "pch.hpp"

#include "Application.hpp"
#include "Engine/Utils/Logger.hpp"
#include "Engine/Events/WindowEvent.hpp"
#include "Engine/Window.hpp"
#include "Engine/Input/Input.hpp"

#include "glad/glad.h"
#include "Engine/Events/MouseEvent.hpp"


namespace Hydrogen
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		H2_CORE_ASSERT(!s_Instance, "An application instance already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Events::Event& e)
	{
		Events::EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<Events::WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			H2_CORE_INFO(e);
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (Layer* l : m_LayerStack)
				l->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(Events::WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}