#include "pch.hpp"
#include "WWindow.hpp"

// Events
#include "Events/WindowEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include "Platform/Windows/Input/WInput.hpp"

#include "Engine/Utils/Logger.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


namespace Hydrogen
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WWindow(props);
	}

	WWindow::WWindow(const WindowProps& props)
	{
		Init(props);
	}

	bool WWindow::initGLloader()
	{
		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		return (success == 1);
	}

	void WWindow::Init(const WindowProps& props)
	{
		Input* s_Instance = new WInput();

		m_Data = WindowData(props);
		H2_CORE_INFO("Creating Window {0} {1} {2}", m_Data.Title, m_Data.Width, m_Data.Height);

		if (!s_GLFWInitialized)
		{
			int sucess = glfwInit();
			H2_CORE_ASSERT(sucess, "Could not initialize GLFW");
			s_GLFWInitialized = true;
		}
		
		m_Window = glfwCreateWindow(static_cast<int>(m_Data.Width), static_cast<int>(m_Data.Height), m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		bool glLoaderStatus = initGLloader();
		H2_CORE_ASSERT(glLoaderStatus, "Failed to initialize GLAD");

		SetVSync(true);
		SetGLFWCallbacks();
	}

	void WWindow::SetGLFWCallbacks()
	{
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				data.Width = width;
				data.Height = height;

				Events::WindowResizeEvent event(width, height);
				data.EventCallbackFn(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window)
			{
				WindowData& data = *(reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				Events::WindowCloseEvent event;
				data.EventCallbackFn(event);
			}
		);

		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				switch (action)
				{
				case GLFW_PRESS:
				{
					Events::KeyPressed event(key, 0);
					data.EventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE:
				{
					Events::KeyReleased event(key);
					data.EventCallbackFn(event);
					break;
				}
				case GLFW_REPEAT:
				{
					Events::KeyPressed event(key, 1);
					data.EventCallbackFn(event);
					break;
				}
				};
			}
		);

		glfwSetScrollCallback(m_Window, 
			[](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				Events::MouseScrolledEvent event(xoffset, yoffset);
				data.EventCallbackFn(event);
			}
		);

		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				Events::MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
				data.EventCallbackFn(event);
			}
		);

		glfwSetMouseButtonCallback(m_Window, 
			[](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						Events::MouseButtonPressed event(button);
						data.EventCallbackFn(event);
						break;
					}
					case GLFW_RELEASE:
					{
						Events::MouseButtonReleased event(button);
						data.EventCallbackFn(event);
						break;
					}
				}
			}
		);
	}

	void WWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WWindow::SetVSync(bool enabled)
	{
		if (enabled) 
			glfwSwapInterval(1);
		else 
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
