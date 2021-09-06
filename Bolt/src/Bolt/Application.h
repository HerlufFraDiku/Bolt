#pragma once

#include "Bolt/Core.h";
#include "Bolt/Window.h"
#include "Bolt/LayerStack.h"
#include "Bolt/Events/Event.h"
#include "Bolt/Events/ApplicationEvent.h"

namespace Bolt {
	class BOLT_API Application {
		public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in client
	Application* CreateApplication();
}

