#pragma once

#include "RendererAPI.hpp"

namespace Hydrogen
{
	/*
	* Static Wrapper around RendererAPI
	*/
	class RenderCommand
	{
	public:
		inline static void Clear(const glm::vec4& color) { s_RendererAPI->Clear(color); }
		inline static void DrawIndexed(const Ref<VertexArray>& va) { s_RendererAPI->DrawIndexed(va); }

	private:
		static RendererAPI* s_RendererAPI;
	};
}