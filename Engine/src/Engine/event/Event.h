#pragma once

namespace Engine 
{

	class ENGINE_API Event
	{

	public:
	
		virtual ~Event() = default;

		bool isHandled() { return m_handled; }
		void setCancelled(bool cancelled) { m_cancelled = cancelled; }

		virtual EventType getEventType() const = 0;

	private:

		bool m_handled = false;
		bool m_cancelled = false;

	};

}
