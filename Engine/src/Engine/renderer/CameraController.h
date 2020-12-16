#pragma once

#include "Engine/Core/TimeStep.h"

#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/ApplicationEvent.h"

#include "Engine/Entity/Camera.h"

namespace Engine
{

	class CameraController
	{

	public:

		virtual void OnUpdate(TimeStep ts) = 0;
		virtual void OnEvent(Event& e) = 0;

		virtual Camera& GetCamera() = 0;
		virtual const Camera& GetCamera() const = 0;

	};

}