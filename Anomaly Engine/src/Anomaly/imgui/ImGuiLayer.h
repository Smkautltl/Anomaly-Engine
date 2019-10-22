#pragma once

#include "Anomaly/Layer.h"

#include "Anomaly/Events/KeyEvent.h"
#include "Anomaly/Events/MouseEvent.h"
#include "Anomaly/Events/ApplicationEvent.h"

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
