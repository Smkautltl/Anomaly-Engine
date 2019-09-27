#pragma once

#include "Anomaly/Core.h"

namespace Anomaly
{
	class ANOMALY_API Input
	{
	public:
		virtual ~Input() = default;
		static bool IsKeyPressed(int KeyCode) { return s_Instance->IsKeyPressedImpl(KeyCode); }

		static bool IsMouseButtonPressed(int Button) { return s_Instance->IsMouseButtonPressedImpl(Button); }
		static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int KeyCode) = 0;

		virtual bool IsMouseButtonPressedImpl(int Button) = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;

	private:
		static Input* s_Instance;
	};
}
