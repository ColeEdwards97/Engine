#pragma once

#include "Engine/World/Transform.h"

#include <glm/glm.hpp>

namespace Engine
{

	enum class ProjectionMode
	{
		Perspective = 0,
		Orthographic = 1
	};

	class Camera
	{

	public:

		Camera();
		Camera(ProjectionMode projectionMode);
		virtual ~Camera() {}

		const Transform& GetTransform() const { return m_Transform; }

		const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		void RecalculateProjectionMatrix();
		void RecalculateViewMatrix();

		// perspective
		void SetPerspective(float fov, float aspect, float zNear, float zFar);
		void SetPerspFOV(float fov);

		// orthographic
		void SetOrthographic(float size, float zNear, float zFar);
		void SetOrthoSize(float size);

		// common
		void SetAspectRatio(float aspect);
		void SetZNear(float zNear);
		void SetZFar(float zFar);

	private:

		void RecalculateProjectionViewMatrix();

	private:

		Transform m_Transform = Transform{};

		glm::mat4 m_ProjectionViewMatrix = glm::mat4(0.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(0.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

		ProjectionMode m_ProjectionMode;

		float m_PerspFov = 45.0f;
		float m_OrthoSize = 1.0f;
		float m_Aspect = 1.6667f;
		float m_ZNear = 0.1f;
		float m_ZFar = 100.0f;

	};

}
