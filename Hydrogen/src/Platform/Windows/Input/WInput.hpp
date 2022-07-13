#pragma once

#include "Input/Input.hpp"
#include "Core.hpp"

namespace Hydrogen
{
	class H2_API WInput
		: public Input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) const override;
		virtual bool isMouseButtonPressedImpl(int button) const override;
		virtual std::pair<double, double> getMousePosImpl() const override;

	};
}

