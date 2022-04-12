#pragma once

/*
* Handels Keyboard Events
* Keyboard events can be:
*	1. KeyPressed
*	2. KeyReleased
*/

#include "Event.hpp"
#include <functional>

namespace Hydrogen
{
	namespace Event
	{
		class H2_API KeyEvent
			: public Event
		{
		protected:
			int m_KeyCode = NULL;

		protected:
			KeyEvent(int keycode)
				: m_KeyCode(keycode)
			{}
		
		public:
			EVENT_CATEGORY(EventCategory::Keyboard | EventCategory::Input)
			inline int GetKeyCode() const { return m_KeyCode; }
		};

		class H2_API KeyPressed
			: public KeyEvent
		{
		private:
			int m_RepeatCount = NULL;

		public:
			KeyPressed(int keycode, int repeatCount)
				: KeyEvent(keycode), m_RepeatCount(repeatCount)
			{}

			EVENT_TYPE(KeyPressed)
			inline int GetRepeatCount() { return m_RepeatCount; }

			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "Key Pressed: " << m_KeyCode << " (" << m_RepeatCount << " repeats)" << std::endl;
				return ss.str();
			}
		};

		class H2_API KeyReleased
			: public KeyEvent
		{
		public:
			KeyReleased(int keycode)
				: KeyEvent(keycode)
			{}

			EVENT_TYPE(KeyReleased)

#ifdef H2_DEBUG
			std::string ToString() const override
			{
				std::stringstream ss;
				ss << "KeyReleasedEvent: " << m_KeyCode;
				return ss.str();
			}
#endif
		};
	}
}