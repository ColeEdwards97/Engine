#pragma once

#include "Engine/world/Transform.h"

#include <glm/glm.hpp>

namespace Engine
{

	class Camera
	{

	public:

		Camera(glm::mat4& projectionMatrix, glm::mat4& viewMatrix);

		Transform& GetTransform() { return m_Transform; }
		void SetTransform(const Transform& transform);

		const glm::mat4& GetViewProjectionMatrix() { return m_ViewProjectionMatrix; }
		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }

		virtual void RecalculateProjectionMatrix() = 0;

	protected:

		glm::mat4 m_ViewProjectionMatrix = glm::mat4(0.0f);
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;

		Transform m_Transform;

	private:

		void RecalculateViewMatrix();
		
	};

}