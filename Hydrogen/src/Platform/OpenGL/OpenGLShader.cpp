#include "pch.hpp"
#include "OpenGLShader.hpp"

#include <glad/glad.h>
#include "glm/gtc/type_ptr.hpp"
#include "Utils/Logger.hpp"
#include "Utils/File.hpp"

namespace Hydrogen
{
	/*shaderBuilder*/

	unsigned int OpenGLShaderBuilder::CompileShader(std::string& source, unsigned int type)
	{
		const char* src = &source[0];

		unsigned int shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		// error handling
		int success;
		char info_log[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, info_log);
			H2_CORE_ERROR("{0} Compilation Failed:\n{1}",
				(type == GL_VERTEX_SHADER) ? "Vertex Shader" : "Fragment Shader",
				info_log);
		}

		return shader;
	}

	unsigned int OpenGLShaderBuilder::CreateShader(const char* vsPath, const char* fsPath)
	{
		std::string vs = File::Read(vsPath);
		std::string fs = File::Read(fsPath);

		unsigned int shaderID = glCreateProgram();

		unsigned int vsID = CompileShader(vs, GL_VERTEX_SHADER);
		unsigned int fsID = CompileShader(fs, GL_FRAGMENT_SHADER);

		glAttachShader(shaderID, vsID);
		glAttachShader(shaderID, fsID);

		glLinkProgram(shaderID);
		glValidateProgram(shaderID);

		glDeleteShader(vsID);
		glDeleteShader(fsID);

		return shaderID;
	}

	/*Shader*/

	OpenGLShader::OpenGLShader(const char* vsPath, const char* fsPath, const char* name)
		: m_PathVS(vsPath), m_PathFS(fsPath), m_Name(name), m_UniformCache()
	{
		m_ShaderID = OpenGLShaderBuilder::CreateShader(vsPath, fsPath);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void OpenGLShader::SetUniform(const char* name, float value, unsigned int count)
	{
		glUniform1fv(GetUniformLocation(name), count, reinterpret_cast<const GLfloat*>(&value));
	}

	void OpenGLShader::SetUniform(const char* name, int value, unsigned int count)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniform(const char* name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetUniform(const char* name, const glm::vec3& value, unsigned int count)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetUniform(const char* name, const glm::vec4& value, unsigned int count)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUniform(const char* name, const glm::mat4& value, unsigned int count, bool transpose)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, transpose, glm::value_ptr(value));
	}

	void OpenGLShader::Bind() const
	{
		int exist;
		glGetProgramiv(m_ShaderID, GL_VALIDATE_STATUS, &exist);
		if (exist)
			glUseProgram(m_ShaderID);
		else
			H2_CORE_WARN("Attempt to bind a non existing shader! {0}", m_Name);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	int OpenGLShader::GetUniformLocation(const char* name)
	{
		if (m_UniformCache.find(name) != m_UniformCache.end())
			return m_UniformCache[name];

		int location = glGetUniformLocation(m_ShaderID, name);
		if (location == -1)
			H2_CORE_WARN("Uniform {0} might not exist!", name);

		m_UniformCache[name] = location;
		return location;
	}
}