#pragma once

#include "Engine/Entity/Camera.h"
#include "Engine/Entity/Component.h"

namespace Engine
{

	class CameraComponent : public Component
	{

	public:

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(Camera* camera)
			: m_Camera(*camera)
		{}

		Camera& GetCamera() { return m_Camera; }

		ALLOWS_MULTIPLE(false);

	private:

		Camera m_Camera;

	};

}