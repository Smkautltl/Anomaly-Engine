#pragma once

#include "Window.h"
#include "LayerStack.h"

#include "../Events/Event.h"
#include "../Events/ApplicationEvent.h"

#include "Anomaly/imgui/ImGuiLayer.h"

namespace Anomaly
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* Overlay);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.f;
	
	private:
		static Application* s_Instance;
	};

	//To be defined in client
	Application* CreateApplication();
}
