#pragma once

#include "Anomaly/Layer.h"

namespace Anomaly
{

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