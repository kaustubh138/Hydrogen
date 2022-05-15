#include "pch.hpp"
#include "WindowsWindow.hpp"

// Events
#include "Events/WindowEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include "Hydrogen/Utils/Logger.hpp"

namespace Hydrogen
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
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
		SetVSync(true);
	}

	void WindowsWindow::SetGLFWCallbacks()
	{
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				data.Width = width;
				data.Height = height;

				Event::WindowResizeEvent event(width, height);
				data.EventCallbackFn(event);
			}
		);

		glfwSetWindowCloseCallback(m_Window,
			[](GLFWwindow* window)
			{
				WindowData& data = *(reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				Event::WindowCloseEvent event;
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
					Event::KeyPressed event(key, 0);
					data.EventCallbackFn(event);
					break;
				}
				case GLFW_RELEASE:
				{
					Event::KeyReleased event(key);
					data.EventCallbackFn(event);
					break;
				}
				case GLFW_REPEAT:
				{
					Event::KeyPressed event(key, 1);
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
				Event::MouseScrolledEvent event(xoffset, yoffset);
				data.EventCallbackFn(event);
			}
		);

		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(reinterpret_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				Event::MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
				data.EventCallbackFn(event);
			}
		);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) 
			glfwSwapInterval(1);
		else 
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
