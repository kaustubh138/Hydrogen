#pragma once

#include "Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace Hydrogen
{
	class OpenGLContext
		: public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	
	private:
		bool initGLloader();
	};
}

