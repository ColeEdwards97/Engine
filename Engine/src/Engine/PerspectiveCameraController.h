#pragma once

#include "Engine/CameraController.h"

#include "Engine/world/Transform.h"

#include "Engine/renderer/PerspectiveCamera.h"

namespace Engine
{

	class PerspectiveCameraController : public CameraController
	{
	public:

		PerspectiveCameraController(float fov, float aspectRatio);
		~PerspectiveCameraController() {}

		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnEvent(Event& e) override;

		virtual Camera& GetCamera() override { return m_Camera; }

	private:

		// MANIPULATION
		void Pan(TimeStep ts);
		void Orbit(TimeStep ts);
		void Look(TimeStep ts);
		void Zoom(TimeStep);
		void CenterView();

		// EVENTS
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);

	private:

		float m_PanSpeed = 5.0f;
		float m_ZoomSpeed = 10.0f;
		float m_RevolveSpeed = 90.0f;

		float m_OrbitDistance = 5.0f;

		glm::vec2 m_LastMousePos = glm::vec2(0.0f);

		Transform m_Transform;
		PerspectiveCamera m_Camera;

	};

}