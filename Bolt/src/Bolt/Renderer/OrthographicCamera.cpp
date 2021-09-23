#include "blpch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Bolt/Renderer/OrthographicCamera.h"

namespace Bolt {
	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom) {
		UpdateProjection(left, right, top, bottom);
	}

	void OrthographicCamera::UpdateProjection(float left, float right, float top, float bottom) {
		BL_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, top, bottom, -1.0f, 1.0f);
		RecalculateViewProjectionMatrix();
	}

	void OrthographicCamera::RecalculateViewProjectionMatrix() {
		BL_PROFILE_FUNCTION();

		// View matrix can be computed as the inverse of the cameras transformation.
		// IE. if the camera moves to the left, objects in the scene will move right in the window. 
		glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transformMatrix);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}