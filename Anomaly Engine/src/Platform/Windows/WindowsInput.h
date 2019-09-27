#pragma once

#include "Anomaly/input.h"

namespace Anomaly
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int KeyCode) override;

		bool IsMouseButtonPressedImpl(int Button) override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
		std::pair<float, float> GetMousePosImpl() override;
	};
}
