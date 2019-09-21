#pragma once

#include "Anomaly/Layer.h"

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
		void OnUpdate() override;
		void OnEvent(Event& event) override;
		
	private:
		float m_Time = 0.f;
	};
	
}