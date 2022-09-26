#include "pch.hpp"

#include "RenderCommand.hpp"
#include "Platform/OpenGL/OpenGLRendererAPI.hpp"

namespace Hydrogen
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}