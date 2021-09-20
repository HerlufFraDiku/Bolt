#include "blpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Bolt {
	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom) {
		// Let GLM compute the orthographic projection matrix
		m_ProjectionMatrix = glm::ortho(left, right, top, bottom, -1.0f, 1.0f);

		// View matrix can be computed as the inverse of the cameras transformation.
		// IE. if the camera moves to the left, objects in the scene will move right in the window. 
		glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transformMatrix);

		// Cache the view * projection to upload to a shader uniform later.
		m_ViewProjectionMatrix =  m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewProjectionMatrix() {
		glm::mat4 transformMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transformMatrix);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}