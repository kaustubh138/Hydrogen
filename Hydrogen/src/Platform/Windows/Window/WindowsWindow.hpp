#pragma once

#include "Hydrogen/Window.hpp"

struct GLFWwindow;

namespace Hydrogen
{
	struct WindowData
	{
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
		std::function<void(Event::Event&)> EventCallbackFn;
	
		WindowData() = default;
		WindowData(const WindowProps& props)
			: Title(props.m_Title), Width(props.m_Width), Height(props.m_Height), VSync(true)
		{}
	};

	class WindowsWindow
		: public Window
	{
	private:
		WindowData m_Data;
		GLFWwindow* m_Window;

	private:
		void SetGLFWCallbacks();
		bool initGLloader();

	public:
		WindowsWindow(const WindowProps& props);
		
		virtual ~WindowsWindow() {};

		void OnUpdate() override;

		inline unsigned int GetHeight() const override { return m_Data.Height; };
		inline unsigned int GetWidth() const override { return m_Data.Width; };

		inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallbackFn = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	};

}

