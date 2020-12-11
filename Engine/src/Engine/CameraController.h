#pragma once

#include "Engine/core/TimeStep.h"

#include "Engine/event/KeyEvent.h"
#include "Engine/event/MouseEvent.h"
#include "Engine/event/ApplicationEvent.h"

#include "Engine/renderer/Camera.h"

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