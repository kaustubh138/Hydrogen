#include "pch.hpp"
#include "Shader.hpp"

#include "Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Hydrogen
{
    Ref<Shader> Shader::Create(const std::string& vs_path, const std::string& fs_path, const std::string& name)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
            {
                H2_CORE_ASSERT(false, "Renderer::None not supported!");
                return nullptr;
                break;
            }
            case RendererAPI::API::OpenGL:
            {
                return std::make_shared<OpenGLShader>(vs_path, fs_path, name);
                break;
            }
            default:
            {
                H2_CORE_ASSERT(false, "Unknown Renderer API")
                    return nullptr;
                break;
            }
        }
    }

	Hydrogen::Ref<Hydrogen::Shader> Shader::Create(const std::string& vs_path, const std::string& fs_path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
		{
			H2_CORE_ASSERT(false, "Renderer::None not supported!");
			return nullptr;
			break;
		}
		case RendererAPI::API::OpenGL:
		{
			return std::make_shared<OpenGLShader>(vs_path, fs_path);
			break;
		}
		default:
		{
			H2_CORE_ASSERT(false, "Unknown Renderer API")
				return nullptr;
			break;
		}
		}
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		std::string name = shader->GetName();
		H2_CORE_ASSERT(!Exists(name), "Shader {0} already exists", name);
        m_Shaders[name] = shader;
    }

	Ref<Shader> ShaderLibrary::Load(const std::string& vsPath, const std::string& fsPath)
	{
		Ref<Shader> newShader = Shader::Create(vsPath, fsPath);
		Add(newShader);
		return newShader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& vsPath, const std::string& fsPath, const std::string& name)
	{
		Ref<Shader> newShader = Shader::Create(vsPath, fsPath, name);
		Add(newShader);
		return newShader;
	}

	Hydrogen::Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		H2_CORE_ASSERT(Exists(name), "Shader {0} not found!", name);
		return m_Shaders[name];
	}
}