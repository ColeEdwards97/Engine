#pragma once

#include "Event.h"

#include "Engine/KeyCodes.h"

namespace Engine
{

	class KeyEvent : public Event
	{
	
	public:

		int getKeyCode() const { return m_keyCode; }

		EventType getEventType() const override { return EventType::KeyboardEvent; }

	protected:

		KeyEvent(const int keyCode)
			: m_keyCode(keyCode)
		{}

	private:

		int m_keyCode;

	};


	class KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(const int keyCode, const uint16_t repeats)
			: KeyEvent(keyCode), m_repeats(repeats)
		{}

		uint16_t getRepeatCount() const { return m_repeats; }

	private:

		uint16_t m_repeats;

	};


	class KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(const int keyCode)
			: KeyEvent(keyCode)
		{}

	};


	class KeyTypedEvent : public KeyEvent
	{
	public:

		KeyTypedEvent(const int keyCode)
			: KeyEvent(keyCode)
		{}

	};
}
