#pragma once

#include "Engine/Core/Input/InputContextStack.h"
#include "Engine/Core/Input/InputConstants.h"
#include "Engine/Event/Event.h"
#include "Engine/Event/KeyEvent.h"
#include "Engine/Event/MouseEvent.h"
#include <glm/glm.hpp>

namespace Engine
{

	class Input : public Subject, public Observer
	{
	public:
		
		// updating state
		void SetInputConstantState(const InputConstant inputConstant, bool pressed, bool repeated);
		void SetInputAxisValue(const InputAxis inputAxis, double value);
		
		// action & range polling
		bool IsActionAvailable(const Action& action) { return m_AvailableInput.Actions.count(action) == 1; }
		bool IsRangeAvailable(const Range& range) { return m_AvailableInput.Ranges.count(range) == 1; }
		double GetRangeValue(const Range& range) { return m_AvailableInput.Ranges.at(range); }
		
		// raw input state polling
		bool IsKeyPressed(const KeyCode key);
		bool IsKeyReleased(const KeyCode key);
		bool IsMouseButtonPressed(const MouseButton button);
		bool IsMouseButtonReleased(const MouseButton button);
		
		glm::vec2 GetMousePosition();
		float GetMouseX();
		float GetMouseY();

		virtual void OnEvent(Event& e) override;

		// create
		static Scope<Input> Create();

	private:
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

	private:
		struct MappedInput {
			std::set<Action> Actions;
			std::unordered_map<Range, double> Ranges;
		};

	private:
		InputContextStack m_Contexts;
		MappedInput m_AvailableInput;

	};

}