#pragma once

#include "Core.hpp"
#include "Event.hpp"

namespace Hydrogen
{
	namespace Events
	{
		class H2_API WindowResizeEvent
			: public Event
		{
		private:
			unsigned int m_Width;
			unsigned int m_Height;

		public:
			WindowResizeEvent(unsigned int toWidth, unsigned int toHeight)
				: m_Width(toWidth), m_Height(toHeight)
			{}

			inline unsigned int GetWidth() { return m_Width; };
			inline unsigned int GetHeight() { return m_Height; };

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "WindowResizeEvent: " << m_Width << ", " << m_Height << '\n';
				return ss.str();
			}

			EVENT_CATEGORY(EventCategory::Application | EventCategory::Dummy)
			EVENT_TYPE(WindowResize)
		};
		
		class H2_API WindowCloseEvent
			: public Event
		{
		public:
			WindowCloseEvent()
			{}

			std::string ToString() const override
			{
				return "WindowCloseEvent";
			}

			EVENT_CATEGORY(EventCategory::Application | EventCategory::Dummy);
			EVENT_TYPE(WindowClose)
		};
	}
}