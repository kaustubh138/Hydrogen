#pragma once

#include "Engine/Renderer/RendererAPI.hpp"

namespace Hydrogen
{
	class OpenGLRendererAPI
		: public RendererAPI
	{
	public:
		virtual void Clear(const glm::vec4& color);

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& va);
	};
}