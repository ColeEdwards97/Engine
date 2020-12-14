#include "engpch.h"

#include "PerspectiveCameraController.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/MouseButtonCodes.h"

#include "Engine/Event/EventDispatcher.h"

#include "Engine/Math/Math.h"

namespace Engine
{

	// TODO: adjust aspect ratio of camera based on new screen size

	PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio)
		: m_Camera(fov, aspectRatio, 0.1f, 100.0f)
	{}


	void PerspectiveCameraController::OnUpdate(TimeStep ts)
	{
		
		if (Input::IsMouseButtonPressed(INPUT_MOUSE_BUTTON_MIDDLE))
		{

			// get mouse delta
			glm::vec2 mousePos = Input::GetMousePosition();
			glm::vec2 deltaPos = glm::normalize(mousePos - m_LastMousePos);

			if (!glm::isnan(deltaPos).x && !glm::isnan(deltaPos.y))
			{
				
				// MIDDLE MOUSE + LEFT MOUSE = Orbit
				if (Input::IsMouseButtonPressed(INPUT_MOUSE_BUTTON_LEFT))
				{
					Orbit(ts, deltaPos);
				}

				// MIDDLE MOUSE + LEFT SHIFT = Look
				else if (Input::IsKeyPressed(INPUT_KEY_LEFT_SHIFT))
				{
					Look(ts, deltaPos);
				}

				// MIDDLE MOUSE + LEFT CTRL = Zoom
				else if (Input::IsKeyPressed(INPUT_KEY_LEFT_CONTROL))
				{
					Zoom(ts, deltaPos);
				}

				// MIDDLE MOUSE ONLY = Pan or Center View
				else
				{
					Pan(ts, deltaPos);
				}

			}

		}

		// update values
		m_LastMousePos = Input::GetMousePosition();

		m_Camera.RecalculateViewMatrix();

	}


	/* MANIPULATION */
	void PerspectiveCameraController::Pan(TimeStep ts, const glm::vec2& deltaPos)
	{
		m_Camera.GetTransform().Translate(ts * m_PanSpeed * -deltaPos.x, m_Camera.GetTransform().GetRight());
		m_Camera.GetTransform().Translate(ts * m_PanSpeed * -deltaPos.y, m_Camera.GetTransform().GetDown());
	}
	
	void PerspectiveCameraController::Orbit(TimeStep ts, const glm::vec2& deltaPos)
	{
		// Set location to orbit location
		m_Camera.GetTransform().SetLocation(m_Camera.GetTransform().GetLocation() + (m_OrbitDistance * m_Camera.GetTransform().GetFront()));

		// Rotate
		m_Camera.GetTransform().Rotate(ts * m_RevolveSpeed * -deltaPos.x, m_Camera.GetTransform().GetUp());
		m_Camera.GetTransform().Rotate(ts * m_RevolveSpeed * -deltaPos.y, m_Camera.GetTransform().GetRight());

		// Move back by the orbit distance
		m_Camera.GetTransform().Translate(m_OrbitDistance, m_Camera.GetTransform().GetBack());
	}
	
	void PerspectiveCameraController::Look(TimeStep ts, const glm::vec2& deltaPos)
	{
		m_Camera.GetTransform().Rotate(ts * m_RevolveSpeed * -deltaPos.x, m_Camera.GetTransform().GetUp());
		m_Camera.GetTransform().Rotate(ts * m_RevolveSpeed * -deltaPos.y, m_Camera.GetTransform().GetRight());
	}
	
	void PerspectiveCameraController::Zoom(TimeStep ts, const glm::vec2& deltaPos)
	{
		m_Camera.GetTransform().Translate(ts * m_ZoomSpeed * deltaPos.y, m_Camera.GetTransform().GetBack());
	}

	void PerspectiveCameraController::CenterView(const glm::vec2& mousePos, const glm::vec2& deltaPos)
	{
		// only do this if there is no change in mouse movement
		if (deltaPos.x == 0.0f && deltaPos.y == 0.0f)
		{
			
		}
	}


	/* EVENTS */
	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(ENG_BIND_EVENT_FN(PerspectiveCameraController::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<WindowResizedEvent>(ENG_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResizedEvent));
	}


	bool PerspectiveCameraController::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		glm::vec2 mousePos = Input::GetMousePosition();
		glm::vec2 deltaPos = mousePos - m_LastMousePos;

		if (e.GetMouseButton() == INPUT_MOUSE_BUTTON_MIDDLE)
		{
			m_LastMousePos = mousePos;
		}
		if (e.GetMouseButton() == INPUT_MOUSE_BUTTON_RIGHT)
		{
			CenterView(mousePos, deltaPos);
		}
		return false;
	}

	bool PerspectiveCameraController::OnWindowResizedEvent(WindowResizedEvent& e)
	{
		m_Camera.SetAspectRatio((float)e.GetWidth() / (float)e.GetHeight());
		return false;
	}


}