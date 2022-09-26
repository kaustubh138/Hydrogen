#include "pch.hpp"
#include "Renderer.hpp"
#include "RenderCommand.hpp"

namespace Hydrogen
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& va)
	{
		va->Bind();
		RenderCommand::DrawIndexed(va);
	}


	void Renderer::EndScene()
	{

	}
}