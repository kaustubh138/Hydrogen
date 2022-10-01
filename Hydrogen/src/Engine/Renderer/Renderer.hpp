#pragma once

#include "RendererAPI.hpp"
#include "Renderer/OrthographicCamera.hpp"
#include "Renderer/Shader/Shader.hpp"

namespace Hydrogen
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);

		static void Submit(const std::shared_ptr<VertexArray>& va, const std::shared_ptr<Shader>& shader);

		static void EndScene();
	
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };
	
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
	
		static std::shared_ptr<SceneData> m_SceneData;
	};

}