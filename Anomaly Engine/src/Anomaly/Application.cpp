#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Anomaly
{
	Application::Application()
	= default;

	Application::~Application()
	= default;

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		AE_TRACE(e);
		
		while (true);
	}

}
