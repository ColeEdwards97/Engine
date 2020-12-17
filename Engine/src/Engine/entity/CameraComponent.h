#pragma once

#include "Engine/Entity/Camera.h"
#include "Engine/Entity/Component.h"

#include "Engine/Core/TimeStep.h"
#include "Engine/Event/Event.h"

namespace Engine
{

	class CameraComponent : public Component
	{

	public:

		void OnUpdate(Camera& camera, TimeStep ts) {}
		void OnEvent(Camera& camera, Event& e) {}

	};

}