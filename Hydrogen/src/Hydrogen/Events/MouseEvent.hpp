#pragma once
#include "pch/pch.hpp"
#include "Event.hpp"

namespace Hydrogen
{
	namespace Events
	{
		class H2_API MouseMovedEvent
			: public Event
		{
		private:
			float m_MouseX, m_MouseY;

		public:
			MouseMovedEvent(float x, float y)
				: m_MouseX(x), m_MouseY(y)
			{}
	
			EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input)
			EVENT_TYPE(MouseMoved)

			inline float GetMouseX() const { return m_MouseX; };
			inline float GetMouseY() const { return m_MouseY; };
			
			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "MouseMovedEvent: " << m_MouseY << ", " << m_MouseY << std::endl;
				return ss.str();
			}
		};

		class H2_API MouseScrolledEvent
			: public Event
		{
		private:
			float m_XOffset, m_YOffset;

		public:
			MouseScrolledEvent(float xOff, float yOff)
				: m_XOffset(xOff), m_YOffset(yOff)
			{}

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "Mouse Scrolled By: " << m_XOffset << " ," << m_YOffset;
				return ss.str();
			}

			EVENT_TYPE(MouseScrolled)
			EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input)
	
			inline float GetXOffset() const{ return m_XOffset; }
			inline float GetYOffset() const{ return m_YOffset; }
		
		};

		class H2_API MouseButtonEvent
			: public Event
		{
		protected:
			int m_ButtonCode;

		public:
			MouseButtonEvent(int code)
				: m_ButtonCode(code)
			{}

			inline int GetButtonCode() const { return m_ButtonCode; }
			EVENT_CATEGORY(EventCategory::Input | EventCategory::MouseButton)
		};

		class H2_API MouseButtonPressed
			: public MouseButtonEvent
		{
		public:
			MouseButtonPressed(int code)
				: MouseButtonEvent(code)
			{}

			EVENT_TYPE(MouseButtonPressed)

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "Mouse Button " << m_ButtonCode << " Pressed";
				return ss.str();
			}
		};		
		
		class H2_API MouseButtonReleased
			: public MouseButtonEvent
		{
		public:
			MouseButtonReleased(int code)
				: MouseButtonEvent(code)
			{}

			EVENT_TYPE(MouseButtonReleased)

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "Mouse Button " << m_ButtonCode << " Released";
				return ss.str();
			}
		};
	}
}