#include <Anomaly.h>
class ExampleLayer : public Anomaly::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		if (Anomaly::Input::IsKeyPressed(AE_KEY_TAB))
			AE_TRACE("Tab Key is pressed");
	}

	void OnEvent(Anomaly::Event& event) override
	{
		if (event.GetEventType() == Anomaly::EventType::KeyPressed)
		{
			Anomaly::KeyPressedEvent& e = (Anomaly::KeyPressedEvent&)event;
			AE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Anomaly::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Anomaly::ImGuiLayer());
	}

	~Sandbox()
	{
		
	}
};

Anomaly::Application* Anomaly::CreateApplication()
{
	return new Sandbox;
}