#pragma once

/*Event Specification and Event Dispatcher*/

#include "Core.hpp"

#include <string>
#include <sstream>
#include <functional>

namespace Hydrogen
{
	namespace Event
	{
#define FLAG(x) (1 << x)

		enum class EventType
		{
			None = 0,																
			WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
			AppTick, AppUpdate, AppRender,												
			KeyPressed, KeyReleased,
			MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
		};

		enum class EventCategory
			: unsigned int
		{
			None			= 0,
			Applicaion		= FLAG(0),
			Input			= FLAG(1),	// Ex. Joystick or Controller
			Keyboard		= FLAG(2),  
			Mouse			= FLAG(3),	
			MouseButton		= FLAG(4),
		};

		using CategoryType = std::underlying_type_t<EventCategory>;

		// Source to_underlying: https://stackoverflow.com/questions/8357240/how-to-automatically-convert-strongly-typed-enum-into-int 
		template <typename E>
		constexpr auto to_underlying(E e) noexcept
		{
			return static_cast<std::underlying_type_t<E>>(e);
		}

		CategoryType operator|(EventCategory A, EventCategory B)
		{
			return (to_underlying(A) | to_underlying(B));
		}

		// Event Specification
		class H2_API Event
		{
			friend class EventDispatcher;

		protected:
			bool m_Handled = false;

		public:
			virtual const char* GetName() const = 0;
			virtual std::string ToString() const { return GetName(); };
			virtual EventType GetEventType() const = 0;
			virtual CategoryType GetEventCategory() const = 0;

			inline bool BelongsToCategory(EventCategory category) 
			{
				return to_underlying(GetEventCategory()) & to_underlying(category);
			}

		};

		class EventDispatcher
		{
		private:
			template <typename T>
			using EventFunc = std::function<bool(T&)>;

		private:
			Event& m_Event;

		public:
			EventDispatcher(Event& e)
				: m_Event(e)
			{}

			template<typename T>
			bool Dispatcher(EventFunc<T> func)
			{
				if (m_Event.GetEventType() == T::GetStaticType())
				{
					m_Event.m_Handled = func(*(T*)&m_Event);
					return true;
				}

				return false;
			}
		};

	// Macros to simplify virtual function implementation
#define EVENT_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
						 virtual EventType GetEventType() const override { return GetStaticType(); }\
						 virtual const char* GetName() const override { return #type; }				
	
#define EVENT_CATEGORY(category) virtual CategoryType GetEventCategory() const override { return category; }
	
		inline std::ostream& operator<<(std::ostream & stream, const Event & e)
		{
			return stream << e.ToString();
		}
	}
}