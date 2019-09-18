#pragma once

#ifdef AE_PLATFORM_WINDOWS

extern Anomaly::Application* Anomaly::CreateApplication();

int main(int argc, char** argv)
{
	auto App = Anomaly::CreateApplication();
	App->Run();
	delete App;
}

#endif