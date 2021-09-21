#pragma once

#include "Bolt/Core.h"
#include "Bolt/Window.h"
#include "Bolt/LayerStack.h"
#include "Bolt/Events/Event.h"
#include "Bolt/Events/ApplicationEvent.h"
#include "Bolt/ImGui/ImGuiLayer.h"
#include "Bolt/Core/Timestep.h"
#include "Bolt/Renderer/Shader.h"
#include "Bolt/Renderer/Buffer.h"
#include "Bolt/Renderer/VertexArray.h"

namespace Bolt {
	class Application {
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
		float m_LastFrameTime = 0.0f;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
	};

	// To be defined in client
	Application* CreateApplication();
}

