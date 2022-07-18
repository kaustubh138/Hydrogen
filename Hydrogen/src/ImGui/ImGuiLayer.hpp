#pragma once

#include "Hydrogen/Core.hpp"
#include "Hydrogen/Layers/Layer.hpp"

// Events
#include "Hydrogen/Events/MouseEvent.hpp"
#include "Hydrogen/Events/KeyEvent.hpp"
#include "Hydrogen/Events/WindowEvent.hpp"

namespace Hydrogen
{

#define BIND_EVENT_FUN(fn) std::bind(&fn, this, std::placeholders::_1)

	using namespace Events;

	class H2_API ImGuiLayer
		: public Layer
	{
	private:
		float m_Time = 0.0f;

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		// Events
		bool onMouseButtonPressedEvent(MouseButtonPressed& e);
		bool onMouseButtonReleasedEvent(MouseButtonReleased& e);
		bool onMouseMovedEvent(MouseMovedEvent& e);
		bool onMouseScrolledEvent(MouseScrolledEvent& e);
		bool onKeyPressedEvent(KeyPressed& e);
		bool onKeyReleasedEvent(KeyReleased& e);
		bool onKeyTypedEvent(KeyTyped& e);
		bool onWindowResizeEvent(WindowResizeEvent& e);
	};
}

