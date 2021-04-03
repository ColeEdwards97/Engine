#include "engpch.h"

#include "Input.h"
#include "Engine/Core/Input/InputConversion.h"
#include "Engine/Event/ActionEvent.h"
#include "Engine/Event/RangeEvent.h"

namespace Engine
{

	void Input::SetInputConstantState(const InputConstant inputConstant, bool pressed, bool repeated)
	{
		for (InputContextStack::const_iterator it = m_Contexts.begin(); it != m_Contexts.end(); ++it)
		{
			const InputContext& context = *(*it);

			// pressed & not held down
			if (pressed && !repeated)
			{
				if (context.IsMappedToAction(inputConstant)) {
					const auto action = context.GetMappedAction(inputConstant);
					m_AvailableInput.Actions.insert(action);
					
					// action begin event
					ActionBeginEvent event(action);
					this->Notify(event);
					return;
				}
			}

			// pressed
			if (pressed)
			{
				if (context.IsMappedToAction(inputConstant)) {
					m_AvailableInput.Actions.insert(context.GetMappedAction(inputConstant));
					return;
				}
			}

			// released. remove any mapped actions
			if (context.IsMappedToAction(inputConstant)) {
				const auto action = context.GetMappedAction(inputConstant);
				m_AvailableInput.Actions.erase(action);
				
				// action end event
				ActionEndEvent event(action);
				this->Notify(event);
			}
		}
	}

	void Input::SetInputAxisValue(const InputAxis inputAxis, double value)
	{
		for (InputContextStack::const_iterator it = m_Contexts.begin(); it != m_Contexts.end(); ++it)
		{
			const InputContext& context = *(*it);
			if (context.IsMappedToRange(inputAxis)) {
				const Range& mappedRange = context.GetMappedRange(inputAxis);
				const double oldValue = m_AvailableInput.Ranges[mappedRange];
				m_AvailableInput.Ranges[mappedRange] = value;
				
				if (oldValue != value) {
					// range changed event
					RangeChangedEvent event(mappedRange, value);
					this->Notify(event);
				}
			}
		}
	}


	void Input::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(ENG_BIND_FN(Input::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(ENG_BIND_FN(Input::OnKeyReleasedEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(ENG_BIND_FN(Input::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(ENG_BIND_FN(Input::OnMouseButtonReleasedEvent));

		dispatcher.Dispatch<MouseMovedEvent>(ENG_BIND_FN(Input::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(ENG_BIND_FN(Input::OnMouseScrolledEvent));
	}

	bool Input::OnKeyPressedEvent(KeyPressedEvent& e) {
		this->SetInputConstantState(InputConversion::KeyCodeToInputConstant(e.GetKeyCode()), true, e.IsRepeated());
		return false;
	}
	bool Input::OnKeyReleasedEvent(KeyReleasedEvent& e) {
		this->SetInputConstantState(InputConversion::KeyCodeToInputConstant(e.GetKeyCode()), false, false);
		return false;
	}
	bool Input::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
		this->SetInputConstantState(InputConversion::MouseButtonToInputConstant(e.GetMouseButton()), true, e.IsRepeated());
		return false;
	}
	bool Input::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
		this->SetInputConstantState(InputConversion::MouseButtonToInputConstant(e.GetMouseButton()), false, false);
		return false;
	}

	bool Input::OnMouseMovedEvent(MouseMovedEvent& e) {
		this->SetInputAxisValue(InputConversion::MouseAxisToInputAxis(MouseAxis::INPUT_AXIS_MOUSE_POS_X), e.GetMouseX());
		this->SetInputAxisValue(InputConversion::MouseAxisToInputAxis(MouseAxis::INPUT_AXIS_MOUSE_POS_Y), e.GetMouseY());
		return false;
	}
	bool Input::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		this->SetInputAxisValue(InputConversion::MouseAxisToInputAxis(MouseAxis::INPUT_AXIS_MOUSE_SCROLL_X), e.GetOffsetX());
		this->SetInputAxisValue(InputConversion::MouseAxisToInputAxis(MouseAxis::INPUT_AXIS_MOUSE_SCROLL_Y), e.GetOffsetY());
		return false;
	}



}