#include "engpch.h"

#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar, float zoom)
		: Camera(glm::ortho(left, right, bottom, top, zNear, zFar), glm::mat4(1.0f)), 
		m_ZNear(zNear), m_ZFar(zFar), m_Zoom(zoom)
	{
		m_AspectRatio = (right - left) / (top - bottom);
	}

	OrthographicCamera::OrthographicCamera(float aspect, float zNear, float zFar, float zoom)
		: Camera(glm::ortho(-aspect/2 * zoom, aspect/2 * zoom, -zoom, zoom, zNear, zFar), glm::mat4(1.0f)),
		m_AspectRatio(aspect), m_ZNear(zNear), m_ZFar(zFar), m_Zoom(zoom)
	{}


	void OrthographicCamera::SetZoom(const float zoom)
	{
		m_Zoom = zoom;
		RecalculateProjectionMatrix();
	}

	void OrthographicCamera::SetAspectRatio(const float aspect)
	{
		m_AspectRatio = aspect;
		RecalculateProjectionMatrix();
	}

	void OrthographicCamera::SetZNear(const float zNear)
	{
		m_ZNear = zNear;
		RecalculateProjectionMatrix();
	}

	void OrthographicCamera::SetZFar(const float zFar)
	{
		m_ZFar = zFar;
		RecalculateProjectionMatrix();
	}


	void OrthographicCamera::RecalculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::ortho(-m_AspectRatio / 2 * m_Zoom, m_AspectRatio / 2 * m_Zoom, -m_Zoom, m_Zoom, m_ZNear, m_ZFar);
	}
	
}