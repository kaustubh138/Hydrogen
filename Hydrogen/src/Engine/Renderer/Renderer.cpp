#include "pch.hpp"
#include "Renderer.hpp"
#include "RenderCommand.hpp"

#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Hydrogen
{
	Ref<Renderer::SceneData> Renderer::m_SceneData = std::make_shared<Renderer::SceneData>();

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