#pragma once

#include "Core.hpp"

namespace Hydrogen
{
	class H2_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instance->isKeyPressedImpl(keycode); }
	
		static bool IsMouseButtonPressed(int buttonCode) { return s_Instance->isMouseButtonPressedImpl(buttonCode); }
		static std::pair<double, double> GetMousePos() { return s_Instance->getMousePosImpl(); };

	protected:
		virtual bool isKeyPressedImpl(int keycode) const = 0;

		virtual bool isMouseButtonPressedImpl(int button) const = 0;
		virtual std::pair<double, double> getMousePosImpl() const = 0;

	private:
		static Input* s_Instance;
	};
}