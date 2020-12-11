#include "engpch.h"

#include "Camera.h"

#include "Engine/utils/QuaternionUtils.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

	Camera::Camera(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
		: m_ProjectionMatrix(projectionMatrix), m_ViewMatrix(viewMatrix)
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	void Camera::SetTransform(const Transform& transform)
	{
		m_Transform = transform;
		RecalculateViewMatrix();
	}
	
	
	/* PROJECTION / VIEW MATRICES */

	void Camera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Transform.GetLocation(), m_Transform.GetLocation() + m_Transform.GetFront(), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	void Camera::RecalculateProjectionViewMatrix()
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}