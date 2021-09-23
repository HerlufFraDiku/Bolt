#include "blpch.h"
#include "Bolt/Utils/OrthographicCameraController.h"
#include "Bolt/Core/Input.h"

namespace Bolt {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool canRotate) : m_CanRotate(canRotate),
		// Initialize the camera using the aspectRatio. 
		// IE. with a 16:9 ratio we get (left, right, top, bottom) to be (-1.77, 1.77, -1, 1) 
		m_Zoom(1.0f), m_AspectRatio(aspectRatio), 
		m_Camera(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom) { }

	void OrthographicCameraController::OnUpdate(Timestep dt) {
		// Move the camera using WASD
		glm::vec3 velocity = glm::vec3(0, 0, 0);
		float rotation = glm::radians(m_Camera.GetRotation());

		if (Input::IsKeyPressed(Key::W)) velocity += glm::vec3(-sin(rotation),  cos(rotation), 0.0f) * m_Movespeed;
		if (Input::IsKeyPressed(Key::A)) velocity -= glm::vec3( cos(rotation),  sin(rotation), 0.0f) * m_Movespeed;
		if (Input::IsKeyPressed(Key::S)) velocity -= glm::vec3( sin(rotation),  cos(rotation), 0.0f) * m_Movespeed;
		if (Input::IsKeyPressed(Key::D)) velocity += glm::vec3( cos(rotation),  sin(rotation), 0.0f) * m_Movespeed;

		m_Camera.SetPosition(m_Camera.GetPosition() + velocity * (float)dt);

		// If rotation is enabled do that using E and Q
		if (m_CanRotate) {
			float rotation = 0.0f;
			if (Input::IsKeyPressed(Key::E)) rotation -= m_Rotatespeed;
			if (Input::IsKeyPressed(Key::Q)) rotation += m_Rotatespeed;
			m_Camera.SetRotation(m_Camera.GetRotation() + rotation * dt);
		}
	}
	
	void OrthographicCameraController::OnEvent(Event& event) {
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(OrthographicCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_FN(OrthographicCameraController::OnMouseScrolled));
	}


	// Recompute aspectRatio on resize and update camera projection accordingly
	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event) {
		m_AspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
		m_Camera.UpdateProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);

		return false;
	}

	// Recompute projection when zoom level changes on scroll
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
		m_Zoom -= event.GetMouseY() * 0.5f;
		m_Zoom = std::max(m_Zoom, 0.25f);
		m_Camera.UpdateProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
		m_Movespeed = m_Zoom;
		return false;
	}
}
