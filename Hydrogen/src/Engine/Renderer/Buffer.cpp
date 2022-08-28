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
    
    /*Buffer Layout*/
    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elems)
        : m_Elements(elems)
    {
        calculateOffsetAndStride();
    }

    void BufferLayout::calculateOffsetAndStride()
    {
        std::size_t offset = 0;
        m_Stride = 0;
        
        for (auto& e : m_Elements)
        {
            e.Offset = offset;
            offset += e.Size;
            m_Stride += e.Size;
        }
    }
    
    std::size_t BufferElement::GetComponentCount() const
    {
        switch (Type)
        {
            case ShaderDataType::Int:     return 1;
            case ShaderDataType::Int2:    return 2;
            case ShaderDataType::Int3:    return 3;
            case ShaderDataType::Int4:    return 4;

            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;

            case ShaderDataType::Mat3:    return 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4;

            case ShaderDataType::Bool:    return 1;
            default:                      H2_CORE_ASSERT(false, "Unknown ShaderDataType!");  return 0;
        }

    }
}
