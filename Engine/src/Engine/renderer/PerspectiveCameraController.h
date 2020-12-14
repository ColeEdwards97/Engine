#pragma once

#include "Engine/Renderer/PerspectiveCamera.h"
#include "Engine/Renderer/CameraController.h"

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
		virtual const Camera& GetCamera() const override { return m_Camera; }

	private:

		// MANIPULATION
		void Pan(TimeStep ts, const glm::vec2& deltaPos);
		void Orbit(TimeStep ts, const glm::vec2& deltaPos);
		void Look(TimeStep ts, const glm::vec2& deltaPos);
		void Zoom(TimeStep, const glm::vec2& deltaPos);
		void CenterView(const glm::vec2& mousePos, const glm::vec2& deltaPos);

		// EVENTS
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnWindowResizedEvent(WindowResizedEvent& e);

	private:

		float m_PanSpeed = 5.0f;
		float m_ZoomSpeed = 10.0f;
		float m_RevolveSpeed = 90.0f;
		float m_OrbitDistance = 5.0f;

		glm::vec2 m_LastMousePos = glm::vec2(0.0f);
		
		PerspectiveCamera m_Camera;

	};

}