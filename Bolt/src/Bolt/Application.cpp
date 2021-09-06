#include "blpch.h"
#include "Bolt/Application.h"
#include "Bolt/Log.h"

#include <Glad/glad.h>

namespace Bolt {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_FN(Application::OnEvent));

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

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event) {
		BL_CORE_TRACE("{0}", event);

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
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}


} 