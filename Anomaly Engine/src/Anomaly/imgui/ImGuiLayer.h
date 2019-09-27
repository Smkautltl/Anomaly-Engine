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
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		 bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		 bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		 bool OnMouseScrollEvent(MouseScrollEvent& e);
		 bool OnMouseMoveEvent(MouseMoveEvent& e);

		 bool OnKeyPressedEvent(KeyPressedEvent& e);
		 bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		 bool OnKeyTypedEvent(KeyTypedEvent& e);

		 bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0.f;
	};
}
