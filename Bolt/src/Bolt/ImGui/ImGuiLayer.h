#pragma once

#include "Bolt/Layer.h"

#include "Bolt/Events/ApplicationEvent.h"
#include "Bolt/Events/KeyEvent.h"
#include "Bolt/Events/MouseEvent.h"

namespace Bolt {

	class BOLT_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}