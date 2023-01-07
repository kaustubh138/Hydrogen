#include "pch.hpp"
#include "Texture.hpp"

#include "Renderer.hpp"
#include "RendererAPI.hpp"
#include "Platform/OpenGL/OpenGLTexture2D.hpp"

namespace Hydrogen
{
    Ref<Texture2D> Texture2D::Create(const std::string& path, const std::string& debug_name = "")
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
                return std::make_shared<OpenGLTexture2D>(path, debug_name);
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