#pragma once

#ifdef BL_PLATFORM_WINDOWS
extern Bolt::Application* Bolt::CreateApplication();

int main(int argc, char** argv) {

	Bolt::Log::Init();

	BL_CORE_WARN("Initialized log!");
	int a = 5;
	BL_INFO("Hello! var={0}", a);


	auto app = Bolt::CreateApplication();
	app->Run();
	delete app;
}
#endif