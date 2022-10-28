#include "pch.hpp"
#include "Shader.hpp"

#include "Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLShader.hpp"

namespace Hydrogen
{
    Shader* Shader::Create(const std::string& vs_path, const std::string& fs_path, const std::string& name)
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
                return new OpenGLShader(vs_path.c_str(), fs_path.c_str(), name.c_str());
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
}