#pragma once
#include <vector>
#include "Bolt/Core/Core.h"
#include "Bolt/Core/Layer.h"

namespace Bolt {
	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }
	
	private:
		std::vector<Layer*> m_layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}

