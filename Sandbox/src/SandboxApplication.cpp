#include "SandboxApplication.hpp"

ExampleLayer::ExampleLayer()
	: Hydrogen::Layer("Example"), m_OrthoCamera(-1.0f, 1.0f, -1.0f, 1.0f)
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

void ExampleLayer::OnUpdate()
{
	Hydrogen::RenderCommand::Clear({ 0.0f, 0.0f, 0.0f, 0.0f });

	Hydrogen::Renderer::BeginScene(m_OrthoCamera);
	m_OrthoCamera.SetPosition({ 0.1f, 0.1f, 0.0f });
	m_OrthoCamera.SetRotation(45.0f);

	m_VertexArray->Bind();
	Hydrogen::Renderer::Submit(m_VertexArray, m_Shader);

	Hydrogen::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Hydrogen::Events::Event& e)
{
	if (e.GetEventType() == Hydrogen::Events::EventType::KeyPressed)
	{
		// Hydrogen::Events::KeyPressed& key_event = static_cast<Hydrogen::Events::KeyPressed&>(e);
		// if (key_event.GetKeyCode() == H2_KEY_TAB)
		// 	H2_TRACE("Tab Key Pressed");
		// H2_TRACE("{0}", (char)key_event.GetKeyCode());
	}
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