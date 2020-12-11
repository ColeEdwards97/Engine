#include "engpch.h"

#include "PerspectiveCameraController.h"

#include "Engine/Input.h"
#include "Engine/KeyCodes.h"
#include "Engine/MouseButtonCodes.h"

#include "Engine/event/EventDispatcher.h"

#include "Engine/math/Math.h"

namespace Engine
{

	// TODO: adjust aspect ratio of camera based on new screen size

	PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio)
		: m_Camera(fov, aspectRatio, 0.1f, 100.0f), m_Transform(Transform()), m_FOV(fov), m_AspectRatio(aspectRatio)
	{
		m_Camera.SetTransform(m_Transform);
	}


	void PerspectiveCameraController::OnUpdate(TimeStep ts)
	{
		
		if (Input::IsMouseButtonPressed(INPUT_MOUSE_BUTTON_MIDDLE))
		{
			// MIDDLE MOUSE + LEFT MOUSE = Orbit
			if (Input::IsMouseButtonPressed(INPUT_MOUSE_BUTTON_LEFT))
			{
				Orbit(ts);
			}

			// MIDDLE MOUSE + LEFT SHIFT = Look
			else if (Input::IsKeyPressed(INPUT_KEY_LEFT_SHIFT))
			{
				Look(ts);
			}

			// MIDDLE MOUSE + LEFT CTRL = Zoom
			else if (Input::IsKeyPressed(INPUT_KEY_LEFT_CONTROL))
			{
				Zoom(ts);
			}

			// MIDDLE MOUSE ONLY = Pan or Center View
			else
			{
				Pan(ts);
			}
		}

		// update values
		m_LastMousePos = Input::GetMousePosition();
		m_Camera.SetTransform(m_Transform);

	}


	/* MANIPULATION */
	void PerspectiveCameraController::Pan(TimeStep ts)
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaPos = glm::normalize(mousePos - m_LastMousePos);

		if (!glm::isnan(deltaPos).x && !glm::isnan(deltaPos.y))
		{
			m_Transform.Translate(ts * m_PanSpeed * -deltaPos.x, m_Transform.GetRight());
			m_Transform.Translate(ts * m_PanSpeed * -deltaPos.y, m_Transform.GetDown());
		}
	}
	
	void PerspectiveCameraController::Orbit(TimeStep ts)
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaPos = glm::normalize(mousePos - m_LastMousePos);

		if (!glm::isnan(deltaPos).x && !glm::isnan(deltaPos.y))
		{
			// Set location to orbit location
			m_Transform.SetLocation(m_Transform.GetLocation() + (m_OrbitDistance * m_Transform.GetFront()));

			// Rotate
			m_Transform.Rotate(ts * m_RevolveSpeed * -deltaPos.x, m_Transform.GetUp());
			m_Transform.Rotate(ts * m_RevolveSpeed * -deltaPos.y, m_Transform.GetRight());

			// Move back by the orbit distance
			m_Transform.Translate(m_OrbitDistance, m_Transform.GetBack());
		}
	}
	
	void PerspectiveCameraController::Look(TimeStep ts)
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaPos = glm::normalize(mousePos - m_LastMousePos);

		if (!glm::isnan(deltaPos).x && !glm::isnan(deltaPos.y))
		{
			m_Transform.Rotate(ts * m_RevolveSpeed * -deltaPos.x, m_Transform.GetUp());
			m_Transform.Rotate(ts * m_RevolveSpeed * -deltaPos.y, m_Transform.GetRight());
		}
	}
	
	void PerspectiveCameraController::Zoom(TimeStep ts)
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaPos = glm::normalize(mousePos - m_LastMousePos);

		if (!glm::isnan(deltaPos).x && !glm::isnan(deltaPos.y))
		{
			m_Transform.Translate(ts * m_ZoomSpeed * deltaPos.y, m_Transform.GetBack());
		}
	}

	void PerspectiveCameraController::CenterView()
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaPos = glm::normalize(mousePos - m_LastMousePos);

		// only do this if there is no change in mouse movement
		if (glm::isnan(deltaPos).x && glm::isnan(deltaPos.y))
		{
			glm::vec3 worldSpace = ScreenToWorld(m_Camera.GetViewProjectionMatrix(), mousePos, glm::vec2(1024.0f, 720.0f));
			
			// Look at the clicked location
			m_Transform.LookAt(worldSpace);

			// Move to the clicked location
			m_Transform.SetLocation(worldSpace);

			// Move back by the orbit distance
			m_Transform.Translate(m_OrbitDistance, m_Transform.GetBack());
		}
	}


	/* EVENTS */
	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(ENG_BIND_EVENT_FN(PerspectiveCameraController::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(ENG_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResizedEvent));
	}


	bool PerspectiveCameraController::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == INPUT_MOUSE_BUTTON_MIDDLE)
		{
			m_LastMousePos = Input::GetMousePosition();
		}
		if (e.GetMouseButton() == INPUT_MOUSE_BUTTON_RIGHT)
		{
			CenterView();
		}
		return false;
	}

	bool PerspectiveCameraController::OnWindowResizedEvent(WindowResizeEvent& e)
	{
		// Reset Aspect Ratio
		return false;
	}


}