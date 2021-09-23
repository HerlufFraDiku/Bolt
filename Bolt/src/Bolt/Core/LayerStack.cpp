#include "blpch.h"
#include "Bolt/Core/LayerStack.h"

namespace Bolt {
	LayerStack::LayerStack() {
	
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer) {
		BL_PROFILE_FUNCTION();

		m_layers.emplace(m_layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		BL_PROFILE_FUNCTION();

		m_layers.emplace_back(overlay);
	}

	void LayerStack::PopLayer(Layer* layer) {
		BL_PROFILE_FUNCTION();

		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		BL_PROFILE_FUNCTION();

		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end()) {
			m_layers.erase(it);
		}
	}
}