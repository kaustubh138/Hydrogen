#pragma once

#include "glm/glm.hpp"
#include "VertexArray.hpp"

namespace Hydrogen
{
	class RendererAPI
	{
	public:
		enum class API
			: unsigned int
		{
			None = 0,
			OpenGL = 1
		};


	public:
		virtual void Clear(const glm::vec4& color) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}