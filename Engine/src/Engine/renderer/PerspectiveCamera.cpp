#include "engpch.h"

#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{


	PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
		: Camera(glm::perspective(glm::radians(fov), aspect, zNear, zFar), glm::mat4(1.0f))
	{}

	void PerspectiveCamera::OnUpdate()
	{
		//RecalculateViewMatrix();
		//RecalculateCameraVectors();
	}

}