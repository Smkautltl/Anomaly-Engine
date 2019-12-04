#pragma once

#ifdef AE_PLATFORM_WINDOWS

//Creates an application that can be used
extern Anomaly::Application* Anomaly::CreateApplication();

int main(int argc, char** argv)
{
	Anomaly::Log::Init();
	AE_CORE_WARN("Initialized Core Log!");
	AE_INFO("Initialized Log!");

	auto App = Anomaly::CreateApplication();
	App->Run();
	delete App;
}

#endif
