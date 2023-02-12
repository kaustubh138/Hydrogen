#include "pch.hpp"

#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Platform/OpenGL/OpenGLVertexArray.hpp"

namespace Hydrogen
{
    Ref<VertexArray> VertexArray::Create()
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
	            return std::make_shared<OpenGLVertexArray>();
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
