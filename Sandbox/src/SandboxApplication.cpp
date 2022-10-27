#include "SandboxApplication.hpp"
#include <glm/gtx/transform.hpp>

ExampleLayer::ExampleLayer()
	: Hydrogen::Layer("Example"), m_OrthoCamera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0.0f)
{
	m_VertexArray.reset(Hydrogen::VertexArray::Create());

	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	std::shared_ptr<Hydrogen::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Hydrogen::VertexBuffer::Create(vertices, sizeof(vertices)));

	{
		Hydrogen::BufferLayout layout = {
			{Hydrogen::ShaderDataType::Float3, "a_Position"}
		};
		vertexBuffer->SetLayout(Hydrogen::BufferLayout(layout));
	}

	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	std::shared_ptr<Hydrogen::IndexBuffer> indexBuffer;
	indexBuffer.reset(Hydrogen::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader.reset(new Hydrogen::Shader("../Hydrogen/res/Shaders/vertex_shader.glsl", "../Hydrogen/res/Shaders/fragment_shader.glsl", "Test"));
}

void ExampleLayer::OnUpdate(Hydrogen::Timestep ts)
{
	if (Hydrogen::Input::IsKeyPressed(H2_KEY_W))
		m_CameraPosition.y -= m_CameraSpeed * ts;
	else if (Hydrogen::Input::IsKeyPressed(H2_KEY_S))
		m_CameraPosition.y += m_CameraSpeed * ts;
	if (Hydrogen::Input::IsKeyPressed(H2_KEY_A))
		m_CameraPosition.x += m_CameraSpeed * ts;
	else if (Hydrogen::Input::IsKeyPressed(H2_KEY_D))
		m_CameraPosition.x -= m_CameraSpeed * ts;

	Hydrogen::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 0.0f });

	Hydrogen::Renderer::BeginScene(m_OrthoCamera);
	m_OrthoCamera.SetPosition(m_CameraPosition);
	m_OrthoCamera.SetRotation(0.0f);

	m_VertexArray->Bind();
	Hydrogen::Renderer::Submit(m_VertexArray, m_Shader);

	Hydrogen::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Hydrogen::Events::Event& e)
{
	
}

Sandbox::Sandbox()
{
	PushLayer(new ExampleLayer());
	PushLayer(new Hydrogen::ImGuiLayer());
}

Sandbox::~Sandbox()
{

}

Hydrogen::Application* Hydrogen::CreateApplication()
{
	return new Sandbox{};
}