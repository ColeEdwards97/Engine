#pragma once

#include "Event.h"

#include "Engine/KeyCodes.h"

namespace Engine
{

	class ENGINE_API KeyEvent : public Event
	{
	
	public:

		int getKeyCode() const { return m_keyCode; }

		int getEventCategoryFlags() const override { return (EventCategoryKeyboard); }

	protected:

		KeyEvent(const int keyCode)
			: m_keyCode(keyCode)
		{}

	private:

		int m_keyCode;

	};


	class ENGINE_API KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(const int keyCode, const uint16_t repeats)
			: KeyEvent(keyCode), m_repeats(repeats)
		{}

		uint16_t getRepeatCount() const { return m_repeats; }

		int getEventCategoryFlags() const override { return (EventCategoryKeyboard | EventCategoryInput); }

	private:

		uint16_t m_repeats;

	};


	class ENGINE_API KeyReleasedEvent : public KeyEvent
	{
	public:

		KeyReleasedEvent(const int keyCode)
			: KeyEvent(keyCode)
		{}

		int getEventCategoryFlags() const override { return (EventCategoryKeyboard | EventCategoryInput); }

	};


	class ENGINE_API KeyTypedEvent : public KeyEvent
	{
	public:

		KeyTypedEvent(const int keyCode)
			: KeyEvent(keyCode)
		{}

		int getEventCategoryFlags() const override { return (EventCategoryKeyboard | EventCategoryInput); }

	};
}
