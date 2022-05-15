#include "pch.hpp"

#include "Application.hpp"
#include "Utils/Logger.hpp"
#include "Events/WindowEvent.hpp"

#include "glad/glad.h"

namespace Hydrogen
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
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

	void Application::OnEvent(Event::Event& e)
	{
		Event::EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<Event::WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
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

	bool Application::OnWindowClose(Event::WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}