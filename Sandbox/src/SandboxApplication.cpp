#include "SandboxApplication.hpp"
#include <glm/gtx/transform.hpp>

ExampleLayer::ExampleLayer()
	: Hydrogen::Layer("Example"), m_OrthoCamera(-1.0f, 1.0f, -1.0f, 1.0f), m_CameraPosition(0.0f)
{
	setupTraingle();
	setupSqaure();
}

void ExampleLayer::setupTraingle()
{
	m_TriangleVA.reset(Hydrogen::VertexArray::Create());

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

	m_TriangleVA->AddVertexBuffer(vertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	std::shared_ptr<Hydrogen::IndexBuffer> indexBuffer;
	indexBuffer.reset(Hydrogen::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0])));
	m_TriangleVA->SetIndexBuffer(indexBuffer);

	m_TriangleShader.reset(new Hydrogen::Shader("../Hydrogen/res/Shaders/triangle_vs.glsl", "../Hydrogen/res/Shaders/triangle_fs.glsl", "TriangleTest"));
}

void ExampleLayer::setupSqaure()
{
	m_SquareVA.reset(Hydrogen::VertexArray::Create());
	
	float squareVertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	std::shared_ptr<Hydrogen::VertexBuffer> squareVB;
	squareVB.reset(Hydrogen::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{Hydrogen::ShaderDataType::Float3, "a_Position"}
	});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Hydrogen::IndexBuffer> squareIB;
	squareIB.reset(Hydrogen::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(squareIndices[0])));
	m_SquareVA->SetIndexBuffer(squareIB);
	
	m_SquareShader.reset(new Hydrogen::Shader("../Hydrogen/res/Shaders/square_vs.glsl", "../Hydrogen/res/Shaders/square_fs.glsl", "SqaureTest"));
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

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Hydrogen::Renderer::Submit(m_SquareVA, m_SquareShader, transform);
		}
	}

	Hydrogen::Renderer::EndScene();
}

void ExampleLayer::OnEvent(Hydrogen::Events::Event& e)
{
	
}

Sandbox::Sandbox()
{
	PushLayer(new ExampleLayer());
}

Sandbox::~Sandbox()
{

}

Hydrogen::Application* Hydrogen::CreateApplication()
{
	return new Sandbox{};
}