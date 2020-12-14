#pragma once

#include "Engine/World/Transform.h"

#include <glm/glm.hpp>

namespace Engine
{

	class Camera
	{

	public:

		Camera(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);

		Transform& GetTransform() { return m_Transform; }
		void SetTransform(const Transform& transform);

		const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }

		virtual void RecalculateProjectionMatrix() = 0;

	protected:

		void RecalculateProjectionViewMatrix();

	protected:

		glm::mat4 m_ProjectionViewMatrix = glm::mat4(0.0f);
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		Transform m_Transform = Transform();
		
	public:

		void RecalculateViewMatrix();

	};

}