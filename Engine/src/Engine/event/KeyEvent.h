#pragma once

#include "Engine/Event/Event.h"
#include "Engine/Core/Input/InputConstants.h"

namespace Engine
{

	class KeyEvent : public Event
	{
	
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(const KeyCode keyCode)
			: m_KeyCode(keyCode)
		{}

	private:
		KeyCode m_KeyCode;

	};


	class KeyPressedEvent : public KeyEvent
	{
	public:

		KeyPressedEvent(const KeyCode keyCode, const bool repeated)
			: KeyEvent(keyCode), m_Repeated(repeated)
		{}

		bool IsRepeated() const { return m_Repeated; }

	private:
		bool m_Repeated;

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
