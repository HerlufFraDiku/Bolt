#include "Application.h"

#include "Bolt/Events/ApplicationEvent.h"
#include "Bolt/Log.h"

namespace Bolt {
	Application::Application() {
	
	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		BL_CORE_TRACE(e);

		while (true);
	}
} 