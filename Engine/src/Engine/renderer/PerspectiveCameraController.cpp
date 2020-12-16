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

	PerspectiveCameraController::PerspectiveCameraController()
		: m_Camera(ProjectionMode::Perspective)
	{
		m_Camera.SetPerspective(45.0f, (1024.0f / 720.0f), 0.1f, 100.0f);
	}


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
		Transform& t = m_Camera.GetTransform();
		t.Translate(ts * m_PanSpeed * -deltaPos.x, t.GetRight());
		t.Translate(ts * m_PanSpeed * -deltaPos.y, t.GetDown());
	}
	
	void PerspectiveCameraController::Orbit(TimeStep ts, const glm::vec2& deltaPos)
	{
		Transform& t = m_Camera.GetTransform();
		
		// Set location to orbit location
		t.SetLocation(t.GetLocation() + (m_OrbitDistance * t.GetFront()));

		// Rotate
		t.Rotate(ts * m_RevolveSpeed * -deltaPos.x, t.GetUp());
		t.Rotate(ts * m_RevolveSpeed * -deltaPos.y, t.GetRight());

		// Move back by the orbit distance
		t.Translate(m_OrbitDistance, t.GetBack());
	}
	
	void PerspectiveCameraController::Look(TimeStep ts, const glm::vec2& deltaPos)
	{
		Transform& t = m_Camera.GetTransform();
		t.Rotate(ts * m_RevolveSpeed * -deltaPos.x, t.GetUp());
		t.Rotate(ts * m_RevolveSpeed * -deltaPos.y, t.GetRight());
	}
	
	void PerspectiveCameraController::Zoom(TimeStep ts, const glm::vec2& deltaPos)
	{
		Transform& t = m_Camera.GetTransform();
		t.Translate(ts * m_ZoomSpeed * deltaPos.y, t.GetBack());
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