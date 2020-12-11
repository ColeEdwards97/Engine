#include "engpch.h"

#include "PerspectiveCamera.h"

#include "Engine/KeyCodes.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{


	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
		: Camera(glm::perspective(glm::radians(fov), aspect, zNear, zFar), glm::mat4(1.0f)), 
		m_FOV(fov), m_AspectRatio(aspect), m_ZNear(zNear), m_ZFar(zFar)
	{}


	void PerspectiveCamera::SetFOV(const float fov)
	{
		m_FOV = fov;
		RecalculateProjectionMatrix();
	}

	void PerspectiveCamera::SetAspectRatio(const float aspect)
	{
		m_AspectRatio = aspect;
		RecalculateProjectionMatrix();
	}

	void PerspectiveCamera::SetZNear(const float zNear)
	{
		m_ZNear = zNear;
		RecalculateProjectionMatrix();
	}

	void PerspectiveCamera::SetZFar(const float zFar)
	{
		m_ZFar = zFar;
		RecalculateProjectionMatrix();
	}
	
	void PerspectiveCamera::RecalculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_ZNear, m_ZFar);
	}

}