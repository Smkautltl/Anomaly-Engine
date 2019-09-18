#pragma once

#ifdef AE_PLATFORM_WINDOWS

extern Anomaly::Application* Anomaly::CreateApplication();

int main(int argc, char** argv)
{
	Anomaly::Log::Init();
	AE_CORE_WARN("Initialized Log!");
	int a = 10;
	AE_INFO("Hello! VAR={0}", a);
	
	auto App = Anomaly::CreateApplication();
	App->Run();
	delete App;
}

#endif