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

namespace Hydrogen
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_OrthoCamera(-1.0f, 1.0f, -1.0f, 1.0f)
	{
		H2_CORE_ASSERT(!s_Instance, "An application instance already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		
		/*------Starter Code---------------*/
		m_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"}
			};
			vertexBuffer->SetLayout(BufferLayout(layout));
		}
	
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(indices[0])));
		m_VertexArray->SetIndexBuffer(indexBuffer);

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
			RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 0.0f });
			
			Renderer::BeginScene(m_OrthoCamera);
			m_OrthoCamera.SetPosition({ 0.1f, 0.1f, 0.0f });
			m_OrthoCamera.SetRotation(45.0f);

			m_VertexArray->Bind();
			Renderer::Submit(m_VertexArray, m_Shader);
	
			Renderer::EndScene();

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