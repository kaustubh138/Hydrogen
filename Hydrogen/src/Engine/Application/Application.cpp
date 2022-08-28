#include "pch.hpp"

#include "Application.hpp"
#include "Engine/Utils/Logger.hpp"
#include "Engine/Events/WindowEvent.hpp"
#include "Engine/Window.hpp"
#include "Engine/Input/Input.hpp"
#include "Engine/Renderer/Buffer.hpp"

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
		
		/*------Starter Code---------------*/
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		//glGenBuffers(1, &m_VertexBuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//glGenBuffers(1, &m_IndexBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(indices[0])));
			
		/*--------Starter Code End-----------*/
		
		m_Shader.reset(new Shader("../Hydrogen/res/Shaders/vertex_shader.glsl", "../Hydrogen/res/Shaders/fragment_shader.glsl", "Test"));
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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