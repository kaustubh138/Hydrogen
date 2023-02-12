#include "Sandbox2D.hpp"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Engine/Renderer/Renderer2D.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{

}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hydrogen::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Hydrogen::RenderCommand::Clear({ 0.1f, 0.1f, 0.1f, 1 });
	
	Hydrogen::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hydrogen::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Hydrogen::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hydrogen::Event& e)
{
	m_CameraController.OnEvent(e);
}