#pragma once

#include "Engine/Entity/GameObject.h"
#include "Engine/Entity/CameraComponent.h"

namespace Engine
{

	class Camera : public GameObject<Camera>
	{

	public:

		Camera()
		{
			// TODO: forward args
			AddComponent<CameraComponent>();
		}

		virtual ~Camera()
		{}

		virtual void OnEnable() override {}
		virtual void OnDisable() override {}

	};

}