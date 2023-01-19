#pragma once

#include "Engine/Renderer/Shader.hpp"
#include "glm/glm.hpp"

namespace Hydrogen
{
	class OpenGLShaderBuilder
	{
	public:
		static unsigned int CompileShader(std::string& source, unsigned int type);
		static unsigned int CreateShader(const std::string& vsPath, const std::string& fsPath);
	};

	class OpenGLShader
		: public Shader
	{
	public:
		OpenGLShader(const std::string& vsPath, const std::string& fsPath, const std::string& name);
		OpenGLShader(const std::string& vsPath, const std::string& fsPath);
		~OpenGLShader();

		void SetUniform(const std::string& name, float value, unsigned int count = 1);
		void SetUniform(const std::string& name, int value, unsigned int count = 1);
		void SetUniform(const std::string& name, const glm::vec2& value);
		void SetUniform(const std::string& name, const glm::vec3& value, unsigned int count = 1);
		void SetUniform(const std::string& name, const glm::mat4& value, unsigned int count = 1, bool transpose = false);
		void SetUniform(const std::string& name, const glm::vec4& value, unsigned int count = 1);

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline int GetUniformLocation(const std::string& name);

		inline unsigned int GetProgramID() { return m_ShaderID; };

	private:
		unsigned int m_ShaderID;
		std::string m_Name;
		std::string m_PathVS;
		std::string m_PathFS;
		std::unordered_map<std::string, int> m_UniformCache;

	};
}

