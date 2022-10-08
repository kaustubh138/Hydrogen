#pragma once

#include "Engine/Core.hpp"
#include "Events/Event.hpp"
#include "Engine/Timestep.hpp"

namespace Hydrogen
{
	class H2_API Layer
	{
	protected:
		std::string m_DebugName;

	public:
		Layer(const std::string& name = "Layer")
			: m_DebugName(name)
		{};

		virtual ~Layer() {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep time_step) {};
		virtual void OnEvent(Events::Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }
	};
}