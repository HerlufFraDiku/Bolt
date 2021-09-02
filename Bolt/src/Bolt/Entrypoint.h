#pragma once

#ifdef BL_PLATFORM_WINDOWS
extern Bolt::Application* Bolt::CreateApplication();

int main(int argc, char** argv) {
	Bolt::Log::Init();

	auto app = Bolt::CreateApplication();
	app->Run();
	delete app;
}
#endif