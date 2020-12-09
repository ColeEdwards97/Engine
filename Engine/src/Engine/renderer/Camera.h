#pragma once

#include <glm/glm.hpp>

namespace Engine
{

	class Camera
	{

	public:

		Camera(glm::mat4& projectionMatrix, glm::mat4& viewMatrix);

		const glm::vec3& GetPosition() { return m_Position; }
		const glm::vec3& GetRotation() { return m_Rotation; }
		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);

		void LookAt(const glm::vec3& target);

		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

		// ON UPDATE
		// TODO: make entity or something
		virtual void OnUpdate() = 0;

	private:

		glm::mat4 m_ViewProjectionMatrix = glm::mat4(0.0f);
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);

	private:

		void RecalculateViewMatrix();
		
	};

}