#pragma once

#include "Camera.h"

namespace Engine
{

	class OrthographicCamera : public Camera
	{

	public:

		OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar);
		OrthographicCamera(float left, float right, float bottom, float top);

	};

}