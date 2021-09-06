#include "blpch.h"
#include "Layer.h"

namespace Bolt {
	Layer::Layer(const std::string& name) : m_DebugName(name) {}
	Layer::~Layer() {}

	void Layer::OnAttach() {}
	void Layer::OnDetach() {}
	void Layer::OnUpdate() {}
	void Layer::OnEvent(Event& event) {}
}