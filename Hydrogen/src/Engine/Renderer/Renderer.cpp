#include "pch.hpp"
#include "Renderer.hpp"
#include "RenderCommand.hpp"
#include "Renderer2D.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Hydrogen
{
	Ref<Renderer::SceneData> Renderer::m_SceneData = std::make_shared<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(std::size_t width, std::size_t height)
	{
		RenderCommand::SetViewPort(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(const Ref<VertexArray>& va, const Ref<Shader>& shader, const glm::mat4& transform_matrix)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniform("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniform("u_Transform", transform_matrix);
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}


	void Renderer::EndScene()
	{

	}
}