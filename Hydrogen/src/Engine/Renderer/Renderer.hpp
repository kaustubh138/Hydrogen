#pragma once

#include "RendererAPI.hpp"
#include "Renderer/OrthographicCamera.hpp"
#include "Renderer/Shader.hpp"

namespace Hydrogen
{
	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);

		static void Submit(const Ref<VertexArray>& va, const Ref<Shader>& shader, const glm::mat4& transform_matrix = glm::mat4(1.0f));

		static void EndScene();
	
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
	
		static Ref<SceneData> m_SceneData;
	};

}