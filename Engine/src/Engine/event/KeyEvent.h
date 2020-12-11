#pragma once

#include "Engine/Event/Event.h"

#include "Engine/Core/KeyCodes.h"

namespace Engine
{

	class KeyEvent : public Event
	{
	
	public:

		int GetKeyCode() const { return m_keyCode; }

		int GetEventCategoryFlags() const override { return (EventCategoryKeyboard); }

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

		uint16_t GetRepeatCount() const { return m_repeats; }

		int GetEventCategoryFlags() const override { return (EventCategoryKeyboard | EventCategoryInput); }

	private:

		uint16_t m_repeats;

	};


	class KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(const int keyCode)
			: KeyEvent(keyCode)
		{}

		int GetEventCategoryFlags() const override { return (EventCategoryKeyboard | EventCategoryInput); }

	};


	class KeyTypedEvent : public KeyEvent
	{
	public:

		KeyTypedEvent(const int keyCode)
			: KeyEvent(keyCode)
		{}

		int GetEventCategoryFlags() const override { return (EventCategoryKeyboard | EventCategoryInput); }

	};
}
