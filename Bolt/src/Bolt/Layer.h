#pragma once

#include "Bolt/Core.h"
#include "Bolt/Events/Event.h"
#include "Bolt/Core/Timestep.h"

namespace Bolt {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate(Timestep deltaTime);
		virtual void OnImGuiRender();
		virtual void OnEvent(Event& event);

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}

