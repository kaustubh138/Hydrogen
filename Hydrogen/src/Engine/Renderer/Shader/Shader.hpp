#pragma once

#include "glm/glm.hpp"

namespace Hydrogen
{
	class ShaderBuilder
	{
	public:
		static unsigned int CompileShader(std::string& source, unsigned int type);
		static unsigned int CreateShader(const char* vsPath, const char* fsPath);
	};

	class Shader
	{
	private:
		const char* m_Name;
		const char* m_PathVS;
		const char* m_PathFS;
		unsigned int m_ShaderID;
		std::unordered_map<const char*, int> m_UniformCache;

	public:
		Shader(const char* vsPath, const char* fsPath, const const char* name);
		~Shader();

		void SetUniform(const char* name, float value, unsigned int count = 1);
		void SetUniform(const char* name, int value, unsigned int count = 1);
		void SetUniform(const char* name, const glm::vec2& value);
		void SetUniform(const char* name, const glm::vec3& value, unsigned int count = 1);
		void SetUniform(const char* name, const glm::mat4& value, unsigned int count = 1, bool transpose = false);
		void SetUniform(const char* name, const glm::vec4& value, unsigned int count = 1);

		void Bind() const;
		void Unbind() const;

		inline int GetUniformLocation(const char* name);

		inline unsigned int GetProgramID() { return m_ShaderID; };
	};
}

