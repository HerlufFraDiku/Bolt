#pragma once

#include <glm/glm.hpp>

namespace Bolt {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float top, float bottom);

		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		const glm::mat4& GetVProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }

		const glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewProjectionMatrix(); }

		float GetRotation() { return m_Rotation; }
		void SetRotation(float degrees) { m_Rotation = degrees; RecalculateViewProjectionMatrix(); }

	private:
		void RecalculateViewProjectionMatrix();

		glm::mat4 m_ViewMatrix = glm::mat4(0.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(0.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(0.0f);

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}