#pragma once
#include "Bolt/Core/Layer.h"
#include "Bolt/Events/ApplicationEvent.h"
#include "Bolt/Events/KeyEvent.h"
#include "Bolt/Events/MouseEvent.h"

namespace Bolt {

	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = false;
	};

}