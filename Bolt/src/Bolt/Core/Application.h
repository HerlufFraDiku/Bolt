#pragma once
#include "Bolt/Core/Core.h"
#include "Bolt/Core/Window.h"
#include "Bolt/Core/LayerStack.h"
#include "Bolt/Core/Timestep.h"
#include "Bolt/Events/Event.h"
#include "Bolt/Events/ApplicationEvent.h"
#include "Bolt/ImGui/ImGuiLayer.h"
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

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		void Close();

	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool Application::OnWindowResize(WindowResizeEvent& event);

	private:
		static Application* s_Instance;
		Scope<Window> m_Window;

		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;
	};

	// To be defined in client
	Application* CreateApplication();
}

