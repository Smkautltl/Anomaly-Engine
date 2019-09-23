#pragma once

#include "Anomaly/input.h"

namespace Anomaly
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int KeyCode) override;

		virtual bool IsMouseButtonPressedImpl(int Button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};
}