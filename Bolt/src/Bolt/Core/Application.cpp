#include "blpch.h"
#include "Bolt/Core/Application.h"
#include "Bolt/Core/Log.h"
#include "Bolt/Renderer/Renderer.h"
#include "Bolt/Renderer/Renderer2D.h"
#include "Bolt/Renderer/RenderCommand.h"

// TODO: Remove this!
#include <GLFW/glfw3.h>

namespace Bolt {
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		BL_PROFILE_FUNCTION();

		BL_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_FN(Application::OnEvent));

		Renderer::Init();
		Renderer2D::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {}

	void Application::Run() {
		while (m_Running) {
			BL_PROFILE_SCOPE("Application update");

			float time = (float)glfwGetTime(); // TODO: Platform::GetTime
			Timestep deltaTime = time - m_LastFrameTime;
			m_LastFrameTime = time;

			{
				BL_PROFILE_SCOPE("Layer Update");
				if (!m_Minimized) for (Layer* layer : m_LayerStack) layer->OnUpdate(deltaTime);
			}

			{
				BL_PROFILE_SCOPE("ImGui Update");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack) layer->OnImGuiRender();	
				m_ImGuiLayer->End();
			}

			{
				BL_PROFILE_SCOPE("Window Update");
				m_Window->OnUpdate();
			}
		}
	}

	void Application::OnEvent(Event& event) {
		BL_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(Application::OnWindowResize));

		// Propagate event from the topmost layer downwards until it was handled.
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(event);
			if (event.Handled) {
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event) {
		BL_PROFILE_FUNCTION();

		if (m_Minimized = event.GetWidth() == 0 || event.GetHeight() == 0) return false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
		return false;
	}

	void Application::PushLayer(Layer* layer) {
		BL_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		BL_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
} 