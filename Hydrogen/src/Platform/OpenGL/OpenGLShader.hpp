#pragma once

#include "Engine/Renderer/Shader.hpp"
#include "glm/glm.hpp"

namespace Hydrogen
{
	class OpenGLShaderBuilder
	{
	public:
		static unsigned int CompileShader(std::string& source, unsigned int type);
		static unsigned int CreateShader(const char* vsPath, const char* fsPath);
	};

	class OpenGLShader
		: public Shader
	{
	public:
		OpenGLShader(const char* vsPath, const char* fsPath, const const char* name);
		~OpenGLShader();

		void SetUniform(const char* name, float value, unsigned int count = 1);
		void SetUniform(const char* name, int value, unsigned int count = 1);
		void SetUniform(const char* name, const glm::vec2& value);
		void SetUniform(const char* name, const glm::vec3& value, unsigned int count = 1);
		void SetUniform(const char* name, const glm::mat4& value, unsigned int count = 1, bool transpose = false);
		void SetUniform(const char* name, const glm::vec4& value, unsigned int count = 1);

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline int GetUniformLocation(const char* name);

		inline unsigned int GetProgramID() { return m_ShaderID; };

	private:
		const char* m_Name;
		const char* m_PathVS;
		const char* m_PathFS;
		unsigned int m_ShaderID;
		std::unordered_map<const char*, int> m_UniformCache;

	};
}

