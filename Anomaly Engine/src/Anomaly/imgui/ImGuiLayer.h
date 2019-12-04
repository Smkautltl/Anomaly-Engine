#pragma once

#include "../Core/Layer.h"

#include "Anomaly/Events/KeyEvent.h"

namespace Anomaly
{
	//This ImGui class is a child class of the layer class and will deal with the imgui events
	class ANOMALY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.f;
	};
}
