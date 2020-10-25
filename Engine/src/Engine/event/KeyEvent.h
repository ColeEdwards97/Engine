#pragma once

#include "Event.h"

#include "Engine/KeyCodes.h"

namespace Engine
{

	class KeyEvent : public Event
	{
	
	public:

		int getKeyCode() const { return m_keyCode; }

		int getEventCategoryFlags() { return (EventCategoryKeyboard); }

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
		
		EventType getEventType() const override { return KeyPressed;}
		int getEventCategoryFlags() const override { return (EventCategoryInput | EventCategoryKeyboard); }

	private:

		uint16_t m_repeats;

	};


	class KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(const int keyCode)
			: KeyEvent(keyCode)
		{}

		EventType getEventType() const override { return KeyReleased; }
		int getEventCategoryFlags() const override { return (EventCategoryInput | EventCategoryKeyboard); }

	};


	class KeyTypedEvent : public KeyEvent
	{
	public:

		KeyTypedEvent(const int keyCode)
			: KeyEvent(keyCode)
		{}

		EventType getEventType() const override { return KeyTyped; }
		int getEventCategoryFlags() const override { return (EventCategoryInput | EventCategoryKeyboard); }

	};
}
