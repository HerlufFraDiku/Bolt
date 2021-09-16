#include "blpch.h"
#include "Bolt/Application.h"
#include "Bolt/Log.h"

#include <Glad/glad.h>

namespace Bolt {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		BL_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event) {
		// BL_CORE_TRACE("{0}", event);

		EventDispatcher dispatcher(event);
		// Bind handler for WindowCloseEvent
		dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(Application::OnWindowClose));

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

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}


} 