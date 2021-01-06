#include "engpch.h"

#include "CameraController.h"
#include "Engine/Entity/EntityManager.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/MouseButtonCodes.h"

#include <glm/glm.hpp>

namespace Engine
{

	CameraController::CameraController(Ref<Camera> camera)
		: m_Camera(camera)
	{}

	CameraController::~CameraController()
	{}

	// UPDATES
	void CameraController::OnUpdate(TimeStep ts)
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
					Orbit(ts, deltaPos);
		
				// MIDDLE MOUSE + LEFT SHIFT = Look
				else if (Input::IsKeyPressed(INPUT_KEY_LEFT_SHIFT))
					Look(ts, deltaPos);
		
				// MIDDLE MOUSE + LEFT CTRL = Zoom
				else if (Input::IsKeyPressed(INPUT_KEY_LEFT_CONTROL))
					Zoom(ts, deltaPos);
		
				// MIDDLE MOUSE ONLY = Pan or Center View
				else
					Pan(ts, deltaPos);
		
			}
		
		}
		
		// update values
		m_LastMousePos = Input::GetMousePosition();
		m_Camera->GetComponent<CameraComponent>()->RecalculateViewMatrix(m_Camera->GetComponent<TransformComponent>()->GetTransform());
		
	}

	// EVENTS
	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(ENG_BIND_EVENT_FN(CameraController::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<WindowResizedEvent>(ENG_BIND_EVENT_FN(CameraController::OnWindowResizedEvent));
	}

	bool CameraController::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
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

	bool CameraController::OnWindowResizedEvent(WindowResizedEvent& e)
	{
		m_Camera->GetComponent<CameraComponent>()->SetAspectRatio((float)e.GetWidth() / (float)e.GetHeight());
		return false;
	}

	// MANIPULATION
	void CameraController::Pan(TimeStep ts, const glm::vec2& deltaPos)
	{
		Transform& t = m_Camera->GetComponent<TransformComponent>()->GetTransform();
		t.Translate(ts * m_PanSpeed * -deltaPos.x, t.GetRight());
		t.Translate(ts * m_PanSpeed * -deltaPos.y, t.GetDown());
	}

	void CameraController::Orbit(TimeStep ts, const glm::vec2& deltaPos)
	{
		Transform& t = m_Camera->GetComponent<TransformComponent>()->GetTransform();
		
		// Set location to orbit location
		t.SetLocation(t.GetLocation() + (m_OrbitDistance * t.GetFront()));
		
		// Rotate
		t.Rotate(ts * m_RevolveSpeed * -deltaPos.x, t.GetUp());
		t.Rotate(ts * m_RevolveSpeed * -deltaPos.y, t.GetRight());
		
		// Move back by the orbit distance
		t.Translate(m_OrbitDistance, t.GetBack());
	}

	void CameraController::Look(TimeStep ts, const glm::vec2& deltaPos)
	{
		Transform& t = m_Camera->GetComponent<TransformComponent>()->GetTransform();
		t.Rotate(ts * m_RevolveSpeed * -deltaPos.x, t.GetUp());
		t.Rotate(ts * m_RevolveSpeed * -deltaPos.y, t.GetRight());
	}

	void CameraController::Zoom(TimeStep ts, const glm::vec2& deltaPos)
	{
		Transform& t = m_Camera->GetComponent<TransformComponent>()->GetTransform();
		t.Translate(ts * m_ZoomSpeed * deltaPos.y, t.GetBack());
	}

	void CameraController::CenterView(const glm::vec2& mousePos, const glm::vec2& deltaPos)
	{

	}


	void CameraController::Possess(EntityID id)
	{
		Ref<IEntity> entity = EntityManager::Get().GetEntity(id);
		if (entity == nullptr)
			return;
		this->Possess(entity);
	}

	void CameraController::Possess(Ref<IEntity> e)
	{
		if (e == nullptr)
			return;
		if (e->GetTypeID() != Camera::GetStaticTypeID())
			return;

		m_Camera = std::static_pointer_cast<Camera>(e);
	}

	void CameraController::Unpossess()
	{
		m_Camera = nullptr;
	}

}