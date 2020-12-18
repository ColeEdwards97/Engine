#pragma once

#include "Engine/Entity/Component.h"
#include "Engine/World/Transform.h"

#include <glm/glm.hpp>

namespace Engine
{

	enum class ProjectionMode
	{
		Perspective = 0,
		Orthographic = 1
	};

	class CameraComponent : public Component<CameraComponent>
	{

	public:

		CameraComponent();
		CameraComponent(ProjectionMode projectionMode);
		virtual ~CameraComponent() {}

		const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		void RecalculateProjectionMatrix();
		void RecalculateViewMatrix(const Transform& transform);

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