#pragma once

#include "Engine/Core.hpp"
#include "Engine/Layers/Layer.hpp"

// Events
#include "Engine/Events/MouseEvent.hpp"
#include "Engine/Events/KeyEvent.hpp"
#include "Engine/Events/WindowEvent.hpp"

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

