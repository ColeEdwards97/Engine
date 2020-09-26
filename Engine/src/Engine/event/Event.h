#pragma once

#include "engpch.h"

namespace Engine 
{

	enum class eventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum eventCategory
	{
		None = 0,
		Application,
		Input,
		Keyboard,
		Mouse,
		MouseButton
	};

	class Event
	{

	public:

		virtual ~Event() = default;
		virtual eventType getEventType() const = 0;		
		static std::underlying_type<eventType>::type getStaticType() { return static_cast<std::underlying_type<eventType>::type>(eventType::AppRender); }

		bool m_handled = false;

	};


	class TestEvent : public Event
	{
	public:

		TestEvent(unsigned int data) : m_data(data) {}

		eventType getEventType() const override { return eventType::AppRender; }
		
		unsigned int getData() const { return m_data; }

	private:
		unsigned int m_data;
	};



}
