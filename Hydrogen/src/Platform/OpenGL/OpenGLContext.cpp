#include "pch.hpp"
#include "OpenGLContext.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hydrogen
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
		H2_CORE_ASSERT(window, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		bool glLoaderStatus = initGLloader();
		H2_CORE_ASSERT(glLoaderStatus, "Failed to initialize GLAD");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
	
	bool OpenGLContext::initGLloader()
	{
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		return (success == 1);
	}
}