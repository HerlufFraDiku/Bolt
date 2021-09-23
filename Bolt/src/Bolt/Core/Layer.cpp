#include "blpch.h"
#include "Bolt/Core/Layer.h"

namespace Bolt {
	Layer::Layer(const std::string& name) : m_DebugName(name) {}
	Layer::~Layer() {}

	void Layer::OnAttach() {}
	void Layer::OnDetach() {}
	void Layer::OnUpdate(Timestep deltaTime) { }
	void Layer::OnImGuiRender() {}
	void Layer::OnEvent(Event& event) {}
}