#include "engpch.h"

#include "Camera.h"

#include "Engine/Entity/CameraComponent.h"

namespace Engine
{

	Camera::Camera(ProjectionMode projectionMode)
		: m_ProjectionMode(projectionMode)
	{
		// ADD COMPONENTS
		AddComponent<TransformComponent>(new TransformComponent());
		AddComponent<CameraComponent>(new CameraComponent());	// dummy component so another camera isnt added
		//AddComponent<CameraControllerComponent>(cameraController);
																	
		// Matrix Calculation
		RecalculateViewMatrix();
		RecalculateProjectionMatrix();
		RecalculateProjectionViewMatrix();
	}
	

	// perspective
	void Camera::SetPerspective(float fov, float aspect, float zNear, float zFar)
	{
		m_PerspFov = fov;
		m_Aspect = aspect;
		m_ZNear = zNear;
		m_ZFar = zFar;
		RecalculateProjectionMatrix();
	}

	void Camera::SetPerspFOV(float fov)
	{
		m_PerspFov = fov;
		RecalculateProjectionMatrix();
	}

	// orthographic
	void Camera::SetOrthographic(float size, float zNear, float zFar)
	{
		m_OrthoSize = size;
		m_ZNear = zNear;
		m_ZFar = zFar;
		RecalculateProjectionMatrix();
	}

	void Camera::SetOrthoSize(float size)
	{
		m_OrthoSize = size;
		RecalculateProjectionMatrix();
	}
	
	// common
	void Camera::SetAspectRatio(float aspect)
	{
		m_Aspect = aspect;
		RecalculateProjectionMatrix();
	}

	void Camera::SetZNear(float zNear)
	{
		m_ZNear = zNear;
		RecalculateProjectionMatrix();
	}

	void Camera::SetZFar(float zFar)
	{
		m_ZFar = zFar;
		RecalculateProjectionMatrix();
	}

	// matrices
	void Camera::RecalculateProjectionViewMatrix()
	{
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateProjectionMatrix()
	{
		switch (m_ProjectionMode)
		{
			case Engine::ProjectionMode::Perspective:
			{
				m_ProjectionMatrix = glm::perspective(glm::radians(m_PerspFov), m_Aspect, m_ZNear, m_ZFar);
				break;
			}
		
			case Engine::ProjectionMode::Orthographic:
			{
				float orthoLeft = -m_OrthoSize * m_Aspect * 0.5f;
				float orthoRight = m_OrthoSize * m_Aspect * 0.5f;
				float orthoBottom = -m_OrthoSize * 0.5f;
				float orthoTop = m_OrthoSize * 0.5f;
				m_ProjectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_ZNear, m_ZFar);
				break;
			}
		}
		RecalculateProjectionViewMatrix();
	}

	void Camera::RecalculateViewMatrix()
	{
		Transform& transform = GetComponent<TransformComponent>().GetTransform();
		m_ViewMatrix = glm::lookAt(transform.GetLocation(), transform.GetLocation() + transform.GetFront(), glm::vec3(0.0f, 1.0f, 0.0f));
		RecalculateProjectionViewMatrix();
		// TODO: glm::vec3(0.0f, 1.0f, 0.0f); to become transform.GetWorld().GetWorldUp();
	}

}