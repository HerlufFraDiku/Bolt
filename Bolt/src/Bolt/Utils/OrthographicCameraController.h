#pragma once
#include "Bolt/Renderer/OrthographicCamera.h"
#include "Bolt/Core/Timestep.h"
#include "Bolt/Events/ApplicationEvent.h"
#include "Bolt/Events/MouseEvent.h"

namespace Bolt {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool canRotate = false);
		void OnUpdate(Timestep dt);
		void OnEvent(Event& event);
		OrthographicCamera& GetCamera() { return m_Camera; }

	private: 
		bool OnWindowResized(WindowResizeEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);

	private:
		float m_Movespeed = 5.0f;
		float m_Rotatespeed = 180.0f;

		float m_AspectRatio = 0.0f;
		float m_Zoom = 1.0f;

		bool m_CanRotate;

		OrthographicCamera m_Camera;
	};
}