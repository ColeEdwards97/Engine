#pragma once

#include "Camera.h"

namespace Engine
{

	class PerspectiveCamera : public Camera
	{

	public:

		PerspectiveCamera(float fov, float aspect, float zNear, float zFar);

		// ON UPDATE
		// TODO: make entity or something
		void OnUpdate() override;

	};

}