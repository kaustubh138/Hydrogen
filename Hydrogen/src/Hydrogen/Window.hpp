#pragma once

#include "pch/pch.hpp"

#include "Core.hpp"

#include "Events/Event.hpp"

namespace Hydrogen
{
	struct WindowProps
	{
		std::string m_Title = "Hydrogen Engine";
		unsigned int m_Width = 1280;
		unsigned int m_Height = 720;
	};

	// Desktop Window Interface
	class H2_API Window
	{
	public:
		virtual ~Window() {} ;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetHeight() const = 0;
		virtual unsigned int GetWidth() const = 0;
	
		using EventCallbackFunction = std::function<void(Event::Event&) > ;
		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& prop = WindowProps());
	};
}