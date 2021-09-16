#pragma once

#include "Bolt/Core.h";
#include "Bolt/Window.h"
#include "Bolt/LayerStack.h"
#include "Bolt/Events/Event.h"
#include "Bolt/Events/ApplicationEvent.h"
#include "Bolt/ImGui/ImGuiLayer.h"

namespace Bolt {
	class BOLT_API Application {
		public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
	};

	// To be defined in client
	Application* CreateApplication();
}

