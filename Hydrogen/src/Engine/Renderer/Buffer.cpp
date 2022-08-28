#include "pch.hpp"
#include "Buffer.hpp"

#include "Renderer/Renderer.hpp"
#include "Platform/OpenGL/OpenGLBuffer.hpp"

namespace Hydrogen
{
    VertexBuffer* VertexBuffer::Create(float* vertices, std::size_t size)
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
                return new OpenGLVertexBuffer(vertices, size);
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
    
    IndexBuffer* IndexBuffer::Create(uint32_t* indices, std::size_t count)
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
                return new OpenGLIndexBuffer(indices, count);
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
