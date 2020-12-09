#include "engpch.h"

#include "Camera.h"

#include "Engine/utils/QuaternionUtils.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

	Camera::Camera(glm::mat4& projectionMatrix, glm::mat4& viewMatrix)
		: m_ProjectionMatrix(projectionMatrix), m_ViewMatrix(viewMatrix)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void Camera::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void Camera::LookAt(const glm::vec3& target)
	{
		SetRotation(LookAtTarget(m_Position, target, glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	void Camera::OnUpdate()
	{
		SetPosition(m_Position);
		SetRotation(m_Rotation);
	}

	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}