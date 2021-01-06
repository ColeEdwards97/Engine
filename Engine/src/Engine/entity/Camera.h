#pragma once

#include "Engine/Entity/GameObject.h"
#include "Engine/Entity/CameraComponent.h"
#include "Engine/Entity/ControllerComponent.h"

namespace Engine
{

	class Camera : public GameObject<Camera>
	{

	public:

		Camera()
		{
			// TODO: forward args
			AddComponent<CameraComponent>();
			AddComponent<ControllerComponent>();
		}

		virtual ~Camera()
		{}

	};

}