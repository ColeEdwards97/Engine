#pragma once

#include <glm/glm.hpp>

namespace Engine
{

	class Camera
	{

	public:

		virtual const glm::vec3& GetPosition() const = 0;
		virtual const glm::vec3& GetRotation() const = 0;
		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual void SetRotation(const glm::vec3& rotation) = 0;

		virtual const glm::mat4& GetViewProjectionMatrix() const = 0;
		virtual const glm::mat4& GetProjectionMatrix() const = 0;
		virtual const glm::mat4& GetViewMatrix() const = 0;


		// ON UPDATE
		// TODO: make entity or something
		virtual void OnUpdate() = 0;

	private:

		virtual void RecalculateViewMatrix() = 0;

	};

}