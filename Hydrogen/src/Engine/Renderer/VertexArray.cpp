#include "pch.hpp"

#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Hydrogen
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::None:
        {
            H2_CORE_ASSERT(false, "Renderer::None not supported!");
            return nullptr;
            break;
        }
        case RendererAPI::OpenGL:
        {
            return new OpenGLVertexArray();
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
