#pragma once
#include "Bolt/Debug/Instrumentation.h"

#ifdef BL_PLATFORM_WINDOWS
extern Bolt::Application* Bolt::CreateApplication();

int main(int argc, char** argv) {
	BL_PROFILE_BEGIN_SESSION("Initialization", "./profile-init.json");
	Bolt::Log::Init();
	auto app = Bolt::CreateApplication();
	BL_PROFILE_END_SESSION();

	BL_PROFILE_BEGIN_SESSION("Runtime", "./profile-runtime.json");
	app->Run();
	BL_PROFILE_END_SESSION();

	BL_PROFILE_BEGIN_SESSION("Shutdown", "./profile-shutdown.json");
	delete app;
	BL_PROFILE_END_SESSION();
}
#endif