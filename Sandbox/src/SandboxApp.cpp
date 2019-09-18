#include <Anomaly.h>

class Sandbox : public Anomaly::Application
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{
		
	}
};

Anomaly::Application* Anomaly::CreateApplication()
{
	return new Sandbox;
}