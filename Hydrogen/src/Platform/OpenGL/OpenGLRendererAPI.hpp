#pragma once

#include "Engine/Renderer/RendererAPI.hpp"

namespace Hydrogen
{
	class OpenGLRendererAPI
		: public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear(const glm::vec4& color);
		virtual void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void DrawIndexed(const Ref<VertexArray>& va);
	};
}