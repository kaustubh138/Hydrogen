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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}

