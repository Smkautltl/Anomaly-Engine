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
		AE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Anomaly::Event& event) override
	{
		AE_TRACE("{0}", event);
	}
};

class Sandbox : public Anomaly::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
		
	}
};

Anomaly::Application* Anomaly::CreateApplication()
{
	return new Sandbox;
}