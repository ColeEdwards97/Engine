#pragma once

#include "Camera.h"

namespace Engine
{

	class PerspectiveCamera : public Camera
	{

	public:

		PerspectiveCamera(float fov, float aspect, float zNear, float zFar);

		const glm::vec3& GetPosition() const override { return m_Position; }
		const glm::vec3& GetRotation() const override { return m_Rotation; }
		void SetPosition(const glm::vec3& position) override;
		void SetRotation(const glm::vec3& rotation) override;

		const glm::mat4& GetViewProjectionMatrix() const override { return m_ViewProjectionMatrix; }
		const glm::mat4& GetProjectionMatrix() const override { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const override { return m_ViewMatrix; }


		// ON UPDATE
		// TODO: make entity or something
		void OnUpdate() override;

	private:

		void RecalculateViewMatrix() override;

	private:

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);

	};

}