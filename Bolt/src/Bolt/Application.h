#pragma once

#include "Bolt/Core.h";
#include "Bolt/Events/Event.h"

namespace Bolt {
	class BOLT_API Application {
		public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}

