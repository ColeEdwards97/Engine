#pragma once

#include "Engine/Event/Event.h"

#include "Engine/Core/Input/KeyCodes.h"

namespace Engine
{

	class KeyEvent : public Event
	{
	
	public:
		KeyCode GetKeyCode() const { return m_keyCode; }

	protected:
		KeyEvent(const KeyCode keyCode)
			: m_keyCode(keyCode)
		{}

	private:
		KeyCode m_keyCode;

	};


	class KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(const KeyCode keyCode, const uint16_t repeats)
			: KeyEvent(keyCode), m_repeats(repeats)
		{}

		uint16_t GetRepeatCount() const { return m_repeats; }

	private:
		uint16_t m_repeats;

	};


	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keyCode)
			: KeyEvent(keyCode)
		{}

	};


	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keyCode)
			: KeyEvent(keyCode)
		{}

	};
}
