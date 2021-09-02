#pragma once

#include "Core.h";

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

