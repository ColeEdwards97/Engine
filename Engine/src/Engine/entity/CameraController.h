#pragma once

#include "Engine/Entity/Controller.h"
#include "Engine/Entity/Camera.h"

#include "Engine/Event/MouseEvent.h"
#include "Engine/Event/ApplicationEvent.h"

namespace Engine
{
	// TODO: split into Keyboard, Gamepad, AI camera controllers
	class CameraController : public Controller
	{
	public:
		CameraController(Ref<Camera> camera);
		virtual ~CameraController();

		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnEvent(Event& e) override;

		virtual void Possess(EntityID id) override;
		virtual void Possess(Ref<IEntity> e) override;
		virtual void Unpossess() override;

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
		// TODO: what happens if camera is DESTROYED
		// nevermind... when an entity is destroyed it should delete its components
		// which will delete the controller component
		// so make sure we delete the controller pointer in the controller component
		Ref<Camera> m_Camera;

		float m_PanSpeed = 5.0f;
		float m_ZoomSpeed = 10.0f;
		float m_RevolveSpeed = 90.0f;
		float m_OrbitDistance = 5.0f;
		glm::vec2 m_LastMousePos = glm::vec2(0.0f);
	};

}